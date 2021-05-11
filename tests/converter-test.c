#include <ctest.h>
#include <internals/converter/convert.h>

CTEST(node_converter, node_1)
{
    string s = convert_node(create("<h1>"), create("test"));
    ASSERT_STR("<h1>test", s->Text(s));
    s->Free(s);
}

CTEST(node_converter, node_2)
{
    string s = convert_node(create("<em>"), create("roflan"));
    ASSERT_STR("<em>roflan", s->Text(s));
    s->Free(s);
}