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
