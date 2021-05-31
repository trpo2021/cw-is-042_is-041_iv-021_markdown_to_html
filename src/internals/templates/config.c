#include <internals/templates/config.h>
#include <stdio.h>

const char* create_template_top()
{
    static char HTML_TEMPLATE_TOP[] = "<!doctype html>\n"
                                      "<html>\n"
                                      "<head>\n"
                                      "<meta charset=\"utf-8\"/>\n"
                                      "<link rel=\"stylesheet\" href=\"template.css\">\n"
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
    char CSS_TEMPLATE[] = "html{\n"
                          "\tfont-family: 'arial'\n"
                          "}\n"
                          "h1{\n"
                          "\tfont-family: 'SmallCaps', sans-serif;\n"
                          "\tfont-size: 2em;\n"
                          "\tfont-weight: bold;\n"
                          "}\n"
                          "li{\n"
                          "\tfont-size: 12px;\n"
                          "}\n";
    FILE* template_css = fopen("style.css", "w");
    fwrite(CSS_TEMPLATE, sizeof(char), sizeof(CSS_TEMPLATE) - 1, template_css);
    fclose(template_css);
}