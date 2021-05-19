#include "parse-single-rule-helper.h"
#include <ctest.h>

CTEST(parse_br_rule, rule_br_correct)
{
    Array(Token) arr = create_test_data(generate_sequence_of_terms(NULL, 0, 0));
    TNode* exp = init_tnode(NodeBreakLine, create_string("<br>"), NULL, false);

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

CTEST(parse_br_rule, rule_br_correct_with_spaces)
{
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){' '}, 1, rand() % 100 + 1));
    TNode* exp = init_tnode(NodeBreakLine, create_string("<br>"), NULL, false);

    RulePerformer perf = {0};
    init_performer(&perf, arr, skip_spaces(0, arr));

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(exp->head->text(exp->head), real->head->text(real->head));
    ASSERT_FALSE(real->nesting);

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}