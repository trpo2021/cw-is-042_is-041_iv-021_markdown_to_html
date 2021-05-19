#include "parse-single-rule-helper.h"
#include <ctest.h>
#include <time.h>

CTEST(parse_hr_rule, rule_hr_correct)
{
    srand(time(NULL));
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){'*', '_'}, 2, rand() % 100 + 3));
    TNode* exp = init_tnode(NodeHorizontalLine, create_string("<hr/>"), NULL, false);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(exp->head->text(exp->head), real->head->text(real->head));
    ASSERT_FALSE(real->nesting);

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

CTEST(parse_hr_rule, rule_hr_correct_with_spaces)
{
    srand(time(NULL));
    String* str = create_string("   _   *   _ ***   ____    ___________ ***** ***\n");
    Array(Token) arr = tokenize(str);
    TNode* exp = init_tnode(NodeHorizontalLine, create_string("<hr/>"), NULL, false);

    RulePerformer perf = {0};
    init_performer(&perf, arr, skip_spaces(0, arr));

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(exp->head->text(exp->head), real->head->text(real->head));
    ASSERT_FALSE(real->nesting);

    str->free(str);
    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

CTEST(parse_hr_rule, rule_hr_incorrect_count_less)
{
    srand(time(NULL));
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){'*', '_', ' '}, 3, rand() % 2));
    TNode* exp = init_tnode(NodeHorizontalLine, create_string("<hr/>"), NULL, false);

    RulePerformer perf = {0};
    init_performer(&perf, arr, skip_spaces(0, arr));

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(exp->type, real->type);

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

CTEST(parse_hr_rule, rule_hr_incorrect_with_others_token)
{
    srand(time(NULL));
    const char tokens[] = "\n_*`=-+<#![> ]()";
    Array(Token) arr = create_test_data(generate_sequence_of_terms(tokens, sizeof(tokens), rand() % 100 + 3));
    TNode* exp = init_tnode(NodeHorizontalLine, create_string("<hr/>"), NULL, false);

    RulePerformer perf = {0};
    init_performer(&perf, arr, skip_spaces(0, arr));

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(exp->type, real->type);

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}