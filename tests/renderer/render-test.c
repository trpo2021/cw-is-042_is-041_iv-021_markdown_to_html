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

CTEST(renderer, render_inline_header_correct)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <h1>test</h1>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("# test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_inline_header_incorrect)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>#test</p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("#test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_underline_header_correct)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <h2>test</h2>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("test\n---");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_underline_header_incorrect)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>---</p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("---\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_underline_header_after_paragraph)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>\n"
                "   test\n"
                "   test 2\n"
                "   ---\n"
                "  </p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("test\ntest 2\n---\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_blockquote_correct)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <blockquote>\n"
                "   <p>test</p>\n"
                "  </blockquote>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("> test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_blockquote_incorrect_with_replace)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>&gt;test</p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("\\>test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_blockquote_incorrect_more_than_allowed)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;&gt;test</p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data(">>>>>>>>>>>>>>>>test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}