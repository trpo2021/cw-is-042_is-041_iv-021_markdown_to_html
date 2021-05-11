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