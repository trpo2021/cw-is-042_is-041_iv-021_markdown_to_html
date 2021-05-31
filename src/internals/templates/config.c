#include <internals/templates/config.h>
#include <stdio.h>

const char* create_template_top()
{
    static char HTML_TEMPLATE_TOP[] = "<!doctype html>\n"
                                      "<html>\n"
                                      "<head>\n"
                                      "<meta charset=\"utf-8\"/>\n"
                                      "<link rel=\"stylesheet\" href=\"style.css\">\n"
                                      "</head>\n";
    return HTML_TEMPLATE_TOP;
}

const char* create_template_bot()
{
    static char HTML_TEMPLATE_BOTTOM[] = "</html>\n";
    return HTML_TEMPLATE_BOTTOM;
}

void create_css()
{
    char CSS_TEMPLATE[] = "html {\n"
                          "\tfont-family: 'SmallCaps', sans-serif;\n"
                          "}\n"
                          "h1 {\n"
                          "\tfont-size: 2em;\n"
                          "\tfont-weight: bold;\n"
                          "}\n"
                          "code, kbd, pre, samp {\n"
                          "\tfont-family: monospace, monospace;\n"
                          "}\n"
                          "code, kbd {\n"
                          "\tfont-size: 1em;\n"
                          "}\n"
                          "code, kbd {\n"
                          "\tpadding: 2px 4px;\n"
                          "}\n"
                          "code {\n"
                          "\tcolor: #c7254e;\n"
                          "\tbackground-color: #f9f2f4;\n"
                          "\tborder-radius: 4px;\n"
                          "}\n"
                          "pre {\n"
                          "\tbackground-color: #f9f2f4;\n"
                          "}\n"
                          "blockquote {\n"
                          "\tborder-left: solid 5px slategrey;\n"
                          "\tpadding-left: 5px;\n"
                          "\tbackground-color: #dadada;\n"
                          "}\n";
    FILE* template_css = fopen("style.css", "w");
    fwrite(CSS_TEMPLATE, sizeof(char), sizeof(CSS_TEMPLATE) - 1, template_css);
    fclose(template_css);
}