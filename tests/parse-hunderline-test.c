#include "parse-single-rule-helper.h"
#include <ctest.h>

static TNode* create_header_from_test_data(char* raw_data)
{
    Array(Token) arr = create_test_data(raw_data);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* result = perf.invoke(&perf, perf.count);

    free_test_data(arr);
    return result;
}

/* in case when we have correct rule ( 2 <= x ('=')) */
CTEST(parse_header_underline_rule, h1_correct)
{
    char* raw_data = generate_sequence_of_terms((char[]){'='}, 1, rand() % 100 + 2);
    TNode* exp = init_tnode(NodeHeadingUnderline, create_string("<h1>"), create_string(raw_data), true);
    TNode* real = create_header_from_test_data(raw_data);

    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(exp->head->text(exp->head), real->head->text(real->head));
    ASSERT_STR(exp->content->text(exp->content), real->content->text(real->content));

    free_tnode(exp);
    free_tnode(real);
}

/* in case when we have correct rule ( 2 <= x ('-')) */
CTEST(parse_header_underline_rule, h2_correct)
{
    char* raw_data = generate_sequence_of_terms((char[]){'-'}, 1, rand() % 100 + 2);
    TNode* exp = init_tnode(NodeHeadingUnderline, create_string("<h2>"), create_string(raw_data), true);
    TNode* real = create_header_from_test_data(raw_data);

    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(exp->head->text(exp->head), real->head->text(real->head));
    ASSERT_STR(exp->content->text(exp->content), real->content->text(real->content));

    free_tnode(exp);
    free_tnode(real);
}

/* in case when we have fewer tokens than allowed */
CTEST(parse_header_underline_rule, h1_incorrect_count_less)
{
    char* raw_data = generate_sequence_of_terms((char[]){'='}, 1, 1);

    TNode* real = create_header_from_test_data(raw_data);

    ASSERT_NOT_EQUAL(NodeHeadingUnderline, real->type);

    free_tnode(real);
}

CTEST(parse_header_underline_rule, h2_incorrect_count_less)
{
    char* raw_data = generate_sequence_of_terms((char[]){'-'}, 1, 1);

    TNode* real = create_header_from_test_data(raw_data);

    ASSERT_NOT_EQUAL(NodeHeadingUnderline, real->type);

    free_tnode(real);
}

/* in case when we have spaces between tokens */
CTEST(parse_header_underline_rule, h1_incorrect_spaces_between)
{
    char* raw_data = generate_sequence_of_terms((char[]){'=', ' '}, 2, rand() % 10000 + 500);

    TNode* real = create_header_from_test_data(raw_data);

    ASSERT_NOT_EQUAL(NodeHeadingUnderline, real->type);

    free_tnode(real);
}

CTEST(parse_header_underline_rule, h2_incorrect_spaces_between)
{
    char* raw_data = generate_sequence_of_terms((char[]){'-', ' '}, 2, rand() % 10000 + 500);

    TNode* real = create_header_from_test_data(raw_data);

    ASSERT_NOT_EQUAL(NodeHeadingUnderline, real->type);

    free_tnode(real);
}