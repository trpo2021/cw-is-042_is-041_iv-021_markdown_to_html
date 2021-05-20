#include "parse-single-rule-helper.h"
#include <ctest.h>

/* in case when we have correct rule ( 2 <= x ('=')) */
CTEST(parse_header_underline_rule, h1_correct)
{
    srand(time(NULL));
    char* raw_data = generate_sequence_of_terms((char[]){'='}, 1, rand() % 100 + 2);
    TNode* exp = init_tnode(NodeHeadingUnderline, create_string("<h1>"), create_string(raw_data), true);
    Array(Token) arr = create_test_data(raw_data);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(exp->head->text(exp->head), real->head->text(real->head));
    ASSERT_STR(exp->content->text(exp->content), real->content->text(real->content));

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

/* in case when we have correct rule ( 2 <= x ('-')) */
CTEST(parse_header_underline_rule, h2_correct)
{
    srand(time(NULL));
    char* raw_data = generate_sequence_of_terms((char[]){'-'}, 1, rand() % 100 + 2);
    TNode* exp = init_tnode(NodeHeadingUnderline, create_string("<h2>"), create_string(raw_data), true);
    Array(Token) arr = create_test_data(raw_data);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(exp->head->text(exp->head), real->head->text(real->head));
    ASSERT_STR(exp->content->text(exp->content), real->content->text(real->content));

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

/* in case when we have fewer tokens than allowed */
CTEST(parse_header_underline_rule, incorrect_count_less)
{
    srand(time(NULL));
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){'='}, 1, 1));

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodeHeadingUnderline, real->type);

    free_test_data(arr);
    free_tnode(real);

    arr = create_test_data(generate_sequence_of_terms((char[]){'-'}, 1, 1));

    init_performer(&perf, arr, 0);

    real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodeHeadingUnderline, real->type);

    free_test_data(arr);
    free_tnode(real);
}

/* in case when we have spaces between tokens */
CTEST(parse_header_underline_rule, incorrect_spaces_between)
{
    srand(time(NULL));
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){'=', ' '}, 2, rand() % 10000 + 500));

    RulePerformer perf = {0};
    init_performer(&perf, arr, skip_spaces(0, arr));

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodeHeadingUnderline, real->type);

    free_test_data(arr);
    free_tnode(real);

    arr = create_test_data(generate_sequence_of_terms((char[]){'-', ' '}, 2, rand() % 10000 + 500));

    init_performer(&perf, arr, 0);

    real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodeHeadingUnderline, real->type);

    free_test_data(arr);
    free_tnode(real);
}