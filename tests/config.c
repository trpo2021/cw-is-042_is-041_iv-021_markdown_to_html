#include <../src/internals/templates/config.h>

const char* create_template_top()
{
    static char HTML_TEMPLATE_TOP[] =
        "<!doctype html>\n<head>\n\t<meta charset=\"utf-8\"/>\n\t<title>Website "
        "name</title>\n\t<link rel=\"stylesheet\" href\"template.css\">\n</head>\n<body>\n";
    return HTML_TEMPLATE_TOP;
}

const char* create_template_bot()
{
    static char HTML_TEMPLATE_BOTTOM[] = "</body>\n</html>\n";
    return HTML_TEMPLATE_BOTTOM;
}

void create_css()
{
    char CSS_TEMPLATE[] = "html{\nfont-famaly: 'arial'\n}\n h1{\nfont-famaly: 'SmallCaps', sans-serif;\nfont-size: "
                          "2em;\nfont-weight: bold;\n}\n li{\nfont-size: 12px;\nfont-capacity: 0.9\n}\n";
    FILE* template_css = fopen("style.css", "w");
    fwrite(CSS_TEMPLATE, sizeof(char), strlen(CSS_TEMPLATE), template_css);
    fclose(template_css);
}