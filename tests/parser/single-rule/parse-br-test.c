#include "parse-single-rule-helper.h"
#include <ctest.h>

/* in case when we have correct rule */
CTEST(parse_br_rule, correct)
{
    Array(Token) arr = create_test_data(generate_sequence_of_terms(NULL, 0, 0));
    TNode* exp = init_tnode(NodeBreakLine, screate("<br>"), NULL, false);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(sraw(exp->head), sraw(real->head));
    ASSERT_FALSE(real->nesting);

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

/* in case when we have spaces strom start of line */
CTEST(parse_br_rule, correct_with_spaces_from_start)
{
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){' '}, 1, rand() % 100 + 1));
    TNode* exp = init_tnode(NodeBreakLine, screate("<br>"), NULL, false);

    RulePerformer perf = {0};
    init_performer(&perf, arr, skip_spaces(0, arr));

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(sraw(exp->head), sraw(real->head));
    ASSERT_FALSE(real->nesting);

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}