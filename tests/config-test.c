#include <ctest.h>
#include <internals/templates/config.h>
#include <stdio.h>

CTEST(template_html, create_top)
{
    ASSERT_STR("<!doctype html>\n"
               "<head>\n"
               "\t<meta charset=\"utf-8\"/>\n"
               "\t<link rel=\"stylesheet\" href\"template.css\">\n"
               "</head>\n"
               "<body>\n",
               create_template_top());
}

CTEST(template_html, create_bot)
{
    ASSERT_STR("</body>\n</html>\n", create_template_bot());
}

CTEST(template_css, template_create)
{
    create_css();
    FILE* fp = fopen("style.css", "r");
    ASSERT_NOT_NULL(fp);
    fclose(fp);
    remove("style.css");
}