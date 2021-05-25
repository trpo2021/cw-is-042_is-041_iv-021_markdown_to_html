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

CTEST(close_tag_func, filled_line)
{
    string s = create("<section>");
    string tmp_s = close_tag(s);
    ASSERT_STR("</section>", tmp_s->Text(tmp_s));
    s->Free(s);
    tmp_s->Free(tmp_s);
}

CTEST(close_tag_func, empty_line)
{
    string s = create("<a>");
    string tmp_s = close_tag(s);
    ASSERT_STR("", tmp_s->Text(tmp_s));
    s->Free(s);
    tmp_s->Free(tmp_s);
}

CTEST(replace_func, test_1)
{
    string s = create("'");
    spec_symblos(s);
    ASSERT_STR("&apos", s->Text(s));
    s->Free(s);
}