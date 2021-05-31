#include "parse-single-rule-helper.h"
#include <ctest.h>

CTEST(parse_img_rule, default_usage)
{
    String* str = screate("![*lolol not italic*](/assets/image.jpg)");

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeImage, real->type);
    ASSERT_STR("<img>", sraw(real->head));

    TNode* link = real->children[0];
    ASSERT_EQUAL(NodeLink, link->type);
    ASSERT_STR("<a>", sraw(link->head));

    ASSERT_EQUAL(NodeSrc, link->children[0]->type);
    ASSERT_STR("<src>", sraw(link->children[0]->head));
    ASSERT_EQUAL(NodeAlt, link->children[1]->type);
    ASSERT_STR("<alt>", sraw(link->children[1]->head));

    ASSERT_STR("*lolol not italic*", sraw(link->children[1]->content));
    ASSERT_STR("href=\"/assets/image.jpg\"", sraw(link->children[0]->content));

    sfree(str);
    free_test_data(arr);
    free_tnode(real);
}