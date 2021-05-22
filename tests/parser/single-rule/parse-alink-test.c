#include "parse-single-rule-helper.h"
#include <ctest.h>

static TNode* create_alink_from_test_data(String* str, const char* link_src)
{
    str->insert(str, link_src, 1);
    str->append(str, '\n');

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* result = perf.invoke(&perf, perf.count);

    str->free(str);
    free_test_data(arr);

    return result;
}

/* in case when we have correct rule */
CTEST(parse_alink_rule, default_usage)
{
    const char* link_src = "https://abc.com/";

    TNode* real = create_alink_from_test_data(create_string("<>"), link_src);

    ASSERT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<a>", real->head->text(real->head));
    ASSERT_STR(link_src, real->children[0]->content->text(real->children[0]->content));

    free_tnode(real);
}

/* in case when we don't have closing tag */
CTEST(parse_alink_rule, without_closing_tag)
{
    const char* link_src = "https://abc.com/";

    TNode* real = create_alink_from_test_data(create_string("<"), link_src);

    ASSERT_NOT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<span>", real->head->text(real->head));
    ASSERT_STR("<", real->content->text(real->content));

    free_tnode(real);
}

/* in case when we don't have link content */
CTEST(parse_alink_rule, without_src)
{
    const char* link_src = "";

    TNode* real = create_alink_from_test_data(create_string("<>"), link_src);

    ASSERT_NOT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<span>", real->head->text(real->head));
    ASSERT_STR("<", real->content->text(real->content));

    free_tnode(real);
}