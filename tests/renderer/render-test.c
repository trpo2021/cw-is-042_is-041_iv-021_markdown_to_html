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