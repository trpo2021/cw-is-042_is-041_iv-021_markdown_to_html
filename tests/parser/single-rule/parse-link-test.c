#include "parse-single-rule-helper.h"
#include <ctest.h>

/* in case when we have correct rule */
CTEST(parse_link_rule, correct)
{
    const char* link_alt = "alt text";
    const char* link_src = "https://abc.com/";

    String* str = create_string("[alt text](https://abc.com/)");

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<a>", real->head->text(real->head));
    const char* alt_text = real->children[0]->children[0]->content->text(real->children[0]->children[0]->content);
    ASSERT_STR(link_alt, alt_text);
    ASSERT_STR(link_src, real->children[1]->content->text(real->children[1]->content));

    str->free(str);
    free_test_data(arr);
    free_tnode(real);
}

/* in case when we have empty alt and src, but it's correct link */
CTEST(parse_link_rule, correct_empty)
{
    String* str = create_string("[]()");

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<a>", real->head->text(real->head));
    ASSERT_NULL(real->children[0]->children);
    ASSERT_STR("", real->children[1]->content->text(real->children[1]->content));

    str->free(str);
    free_test_data(arr);
    free_tnode(real);
}

/* in case when we don't have any op or cl tag */
CTEST(parse_link_rule, without_any_tag)
{
    char* test_data[] = {"]()", "[()", "[])", "[]("};

    for (size_t i = 0; i < 4; ++i)
    {
        String* str = create_string(test_data[i]);
        Array(Token) arr = tokenize(str);

        RulePerformer perf = {0};
        init_performer(&perf, arr, 0);
        TNode* real = perf.invoke(&perf, perf.count);

        ASSERT_NOT_EQUAL(NodeLink, real->type);
        ASSERT_STR("<span>", real->head->text(real->head));
        ASSERT_STR(test_data[i], real->content->text(real->content));

        str->free(str);
        free_test_data(arr);
        free_tnode(real);
    }
}

/* in case when we have spaces or something else after [] */
CTEST(parse_link_rule, with_anything_between_alt_and_src)
{
    srand(time(NULL));
    String* str = create_string("[]");
    const char tokens[] = "\n_*`=-+<#![>";
    str->append(str, tokens[rand() % (sizeof(tokens) - 1)]);
    str->concat(str, "()");
    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);
    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodeLink, real->type);
    ASSERT_STR("<span>", real->head->text(real->head));
    ASSERT_STR("[]", real->content->text(real->content));

    str->free(str);
    free_test_data(arr);
    free_tnode(real);
}