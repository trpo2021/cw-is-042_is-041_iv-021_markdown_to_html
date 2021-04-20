#include <../src/internals/templates/config.h>
#include <ctest.h>
#include <stdio.h>

CTEST(template_html, create_top)
{
    ASSERT_STR("<!doctype html>\n<head>\n\t<meta charset=\"utf-8\"/>\n\t<title>Website "
               "name</title>\n\t<link rel=\"stylesheet\" href\"template.css\">\n</head>\n<body>\n",
               create_template_top());
}

CTEST(template_html, create_bot)
{
    ASSERT_STR("</body>\n</html>\n", create_template_bot());
}

CTEST(template_css, template_create)
{
    create_css();
    ASSERT_NOT_NULL(fopen("style.css", "r"));
}