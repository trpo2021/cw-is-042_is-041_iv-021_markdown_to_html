#include <stdio.h>
#include <string.h>

void create_template()
{
    char HTML_TEMPLATE_TOP[] = "<!doctype html>\n<head>\n\t<meta charset=\"utf-8\"/>\n\t<title>Website name</title>\n\t<link rel=\"stylesheet\" href\"template.css\">\n</head>\n</body>\n";
    char HTML_TEMPLATE_BOTTOM[] = "</body>\n</html>\n";
    char CSS_TEMPLATE[] = "html{\nfont-famaly: 'arial'\n}\n h1{\nfont-famaly: 'SmallCaps', sans-serif;\nfont-size: 2em;\nfont-weight: bold;\n}\n li{\nfont-size: 12px;\nfont-capacity: 0.9\n}\n";

    FILE *template_css = fopen("template.css", "w");
    FILE *template_top = fopen("template_top.html", "w");
    FILE *template_bottom = fopen("template_bottom.html", "w");

    fwrite(HTML_TEMPLATE_TOP, sizeof(char), strlen(HTML_TEMPLATE_TOP) + 1, template_top);
    fwrite(HTML_TEMPLATE_BOTTOM, sizeof(char), strlen(HTML_TEMPLATE_BOTTOM) + 1, template_bottom);
    fwrite(CSS_TEMPLATE, sizeof(char), strlen(CSS_TEMPLATE) + 1, template_css);
}