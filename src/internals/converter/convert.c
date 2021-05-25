#include <internals/converter/convert.h>

string convert_node(string head, string content)
{
    string tmp = create("");
    tmp->Concat(tmp, head->Text(head));
    tmp->Concat(tmp, content->Text(content));
    head->Free(head);
    content->Free(content);
    return tmp;
}

string close_tag(string head)
{
    if (!head->Compare(head, "<br>") && !head->Compare(head, "<hr/>") && !head->Compare(head, "<a>"))
    {
        string tmp = head->Copy(head);
        tmp->Insert(tmp, "/", 1);
        return tmp;
    }
    else
    {
        return create("");
    }
}

void spec_symblos(string content)
{
    TagList spec_list = {
        .tags[0] = {"'", "&apos"},
        .tags[1] = {"\"", "&quot"},
        .tags[2] = {"&", "&amp"},
        .tags[3] = {"<", "&lt"},
        .tags[4] = {">", "&gt"},
    };

    for (int i = 0; i < 5; i++)
    {
        if (content->Contains(content, spec_list.tags[i].key))
        {
            content->Replace(content, spec_list.tags[i].value, spec_list.tags[i].key);
        }
    }
}