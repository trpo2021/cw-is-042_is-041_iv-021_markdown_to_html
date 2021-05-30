#include "parse-single-rule-helper.h"
#include <ctest.h>

/* in case when we have correct rule */
CTEST(parse_link_rule, correct)
{
    const char* link_alt = "alt text";

    String* str = screate("[alt text](https://abc.com/)");

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<a>", sraw(real->head));
    ASSERT_STR("href=\"https://abc.com/\"", sraw(real->children[0]->content));
    const char* alt_text = sraw(real->children[1]->children[0]->content);
    ASSERT_STR(link_alt, alt_text);

    sfree(str);
    free_test_data(arr);
    free_tnode(real);
}

/* in case when we have empty alt and src, but it's correct link */
CTEST(parse_link_rule, correct_empty)
{
    String* str = screate("[]()");

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<a>", sraw(real->head));
    ASSERT_NULL(real->children[0]->children);
    ASSERT_STR("", sraw(real->children[0]->content));

    sfree(str);
    free_test_data(arr);
    free_tnode(real);
}

/* in case when we don't have any op or cl tag */
CTEST(parse_link_rule, without_any_tag)
{
    char* test_data[] = {"]()", "[()", "[])", "[]("};

    for (size_t i = 0; i < 4; ++i)
    {
        String* str = screate(test_data[i]);
        Array(Token) arr = tokenize(str);

        RulePerformer perf = {0};
        init_performer(&perf, arr, 0);
        TNode* real = perf.invoke(&perf, perf.count);

        ASSERT_NOT_EQUAL(NodeLink, real->type);
        ASSERT_STR("<span>", sraw(real->head));
        ASSERT_STR(test_data[i], sraw(real->content));

        sfree(str);
        free_test_data(arr);
        free_tnode(real);
    }
}

/* in case when we have spaces or something else after [] */
CTEST(parse_link_rule, with_anything_between_alt_and_src)
{
    srand(time(NULL));
    String* str = screate("[]");
    const char tokens[] = "\n_*`=-+<#![>";
    sappend(str, tokens[rand() % (sizeof(tokens) - 1)]);
    sconcat(str, "()");
    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);
    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<span>", sraw(real->head));
    ASSERT_STR("[]", sraw(real->content));

    sfree(str);
    free_test_data(arr);
    free_tnode(real);
}