#include <ctest.h>
#include <internals/renderer/renderer.h>

static String* create_test_data(const char* raw)
{
    String* markdown = screate(raw);
    String* html = render_html(markdown);
    sfree(markdown);
    return html;
}

CTEST(renderer, render_empty)
{
    char* raw = "<body>\n"
                " <section>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_hr)
{
    char* raw = "<body>\n"
                " <section>\n"
                " </section>\n"
                " <hr/>\n"
                " <section>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("______");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_paragraph_single)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>test</p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_paragraph_multiline)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>\n"
                "   test\n"
                "   test 2\n"
                "  </p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("test\ntest 2\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_paragraph_single_with_breakline)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>test  <br></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("test  \n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_paragraph_multiline_with_breakline)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>\n"
                "   test  \n"
                "    <br>\n"
                "   test 2\n"
                "  </p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("test  \ntest 2\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}