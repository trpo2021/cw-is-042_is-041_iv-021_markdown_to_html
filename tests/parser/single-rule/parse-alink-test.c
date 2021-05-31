#include "parse-single-rule-helper.h"
#include <ctest.h>

static TNode* create_alink_from_test_data(String* str, const char* link_src)
{
    sinsert(str, link_src, 1);
    sappend(str, '\n');

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* result = perf.invoke(&perf, perf.count);

    sfree(str);
    free_test_data(arr);

    return result;
}

/* in case when we have correct rule */
CTEST(parse_alink_rule, default_usage)
{
    const char* link_src = "https://abc.com/";

    TNode* real = create_alink_from_test_data(screate("<>"), link_src);

    ASSERT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<a>", sraw(real->head));
    ASSERT_STR("href=\"https://abc.com/\"", sraw(real->children[0]->content));

    free_tnode(real);
}

/* in case when we don't have closing tag */
CTEST(parse_alink_rule, without_closing_tag)
{
    const char* link_src = "https://abc.com/";

    TNode* real = create_alink_from_test_data(screate("<"), link_src);

    ASSERT_NOT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<span>", sraw(real->head));
    ASSERT_STR("<", sraw(real->content));

    free_tnode(real);
}

/* in case when we don't have link content */
CTEST(parse_alink_rule, without_src)
{
    const char* link_src = "";

    TNode* real = create_alink_from_test_data(screate("<>"), link_src);

    ASSERT_NOT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<span>", sraw(real->head));
    ASSERT_STR("<", sraw(real->content));

    free_tnode(real);
}