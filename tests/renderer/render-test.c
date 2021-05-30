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

CTEST(renderer, render_ul)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <ul>\n"
                "   <li>\n"
                "    <p>test</p>\n"
                "   </li>\n"
                "  </ul>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("+ test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
    html = create_test_data("* test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
    html = create_test_data("- test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_ol)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <ol>\n"
                "   <li>\n"
                "    <p>test</p>\n"
                "   </li>\n"
                "  </ol>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("1. test\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_combined_lists)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <ol>\n"
                "   <li>\n"
                "    <p>test</p>\n"
                "   </li>\n"
                "   <li>\n"
                "    <p>test 2</p>\n"
                "    <ul>\n"
                "     <li>\n"
                "      <p>test 3</p>\n"
                "     </li>\n"
                "    </ul>\n"
                "   </li>\n"
                "  </ol>\n"
                "  <ul>\n"
                "   <li>\n"
                "    <p>test 4</p>\n"
                "   </li>\n"
                "  </ul>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("1. test\n"
                                    "2. test 2\n"
                                    "    * test 3\n"
                                    "+ test 4\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_codeblock)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <pre>\n"
                "   <code>\n"
                "    &lt;test with replace&gt;\n"
                "   </code>\n"
                "  </pre>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("```\n"
                                    "<test with replace>\n"
                                    "```\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_codeblock_empty)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <pre>\n"
                "   <code>\n"
                "   </code>\n"
                "  </pre>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("```\n"
                                    "```\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_code_inline)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><code>&lt;test&gt;</code></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("`<test>`\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_bold)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><strong>test</strong></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("**test**\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_italic)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><em>test</em></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("*test*\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_bold_italic)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><strong><em>test</em></strong></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("***test***\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_autolink_email_correct)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a href=\"mailto:azbuka@gmail.com\">azbuka@gmail.com</a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("<azbuka@gmail.com>\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_autolink_email_incorrect)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>&lt;azbukagmail.com&gt;</p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("<azbukagmail.com>\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_autolink_local_correct)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a href=\"/about/index.html\">/about/index.html</a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("</about/index.html>\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_autolink_local_incorrect)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>&lt;about/index.html&gt;</p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("<about/index.html>\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_autolink_url_short_correct)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a href=\"http://www.youtube.com\">www.youtube.com</a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("<www.youtube.com>\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_autolink_url_short_incorrect)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>&lt;ww.youtube.com&gt;</p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("<ww.youtube.com>\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_autolink_url_correct)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a href=\"https://www.youtube.com\">https://www.youtube.com</a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("<https://www.youtube.com>\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_autolink_url_incorrect)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p>&lt;https//www.youtube.com&gt;</p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("<https//www.youtube.com>\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_link_correct)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a href=\"https://www.youtube.com\">alt text</a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("[alt text](https://www.youtube.com)\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_link_empty_correct)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a></a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("[]()\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_link_alt_with_empty_src)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a>alt text</a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("[alt text]()\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_link_alt_bold)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a href=\"https://www.youtube.com\"><strong>alt text</strong></a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("[**alt text**](https://www.youtube.com)\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_link_alt_italic)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a href=\"https://www.youtube.com\"><em>alt text</em></a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("[*alt text*](https://www.youtube.com)\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_link_alt_bold_italic)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a href=\"https://www.youtube.com\"><strong><em>alt text</em></strong></a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("[***alt text***](https://www.youtube.com)\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_link_alt_code)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><a href=\"https://www.youtube.com\"><code>alt text</code></a></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("[`alt text`](https://www.youtube.com)\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_link_alt_another_link)
{
    char* raw =
        "<body>\n"
        " <section>\n"
        "  <p><a href=\"https://www.youtube.com\"><a href=\"mailto:example@gmail.com\">example@gmail.com</a></a></p>\n"
        " </section>\n"
        "</body>\n";
    String* html = create_test_data("[<example@gmail.com>](https://www.youtube.com)\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_image)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><img src=\"/assets/player.png\" alt=\"<im@not.linkbtw>\"></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("![<im@not.linkbtw>](/assets/player.png)\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}

CTEST(renderer, render_image_empty)
{
    char* raw = "<body>\n"
                " <section>\n"
                "  <p><img></p>\n"
                " </section>\n"
                "</body>\n";
    String* html = create_test_data("![]()\n");
    ASSERT_STR(raw, sraw(html));
    sfree(html);
}