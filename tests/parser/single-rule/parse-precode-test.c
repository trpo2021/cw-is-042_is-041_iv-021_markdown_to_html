#include "parse-single-rule-helper.h"
#include <ctest.h>

/* in case when we have correct rule (3 <= x ('`')) */
CTEST(parse_precode_rule, correct)
{
    srand(time(NULL));
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){'`'}, 1, rand() % 100 + 3));
    TNode* exp = init_tnode(NodePre, screate("<pre>"), NULL, true);
    TNode* exp_chd_lvl1 = init_tnode(NodeCode, screate("<code>"), NULL, true);
    TNode* exp_chd_lvl2 = init_tnode(NodeSpan, screate("<span>"), NULL, false);
    add_tnode(exp, exp_chd_lvl1);
    add_tnode(exp_chd_lvl1, exp_chd_lvl2);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    TNode* cur_exp = exp;
    TNode* cur_real = real;

    for (size_t i = 0; i < 3; ++i)
    {
        ASSERT_EQUAL(cur_exp->type, cur_real->type);
        ASSERT_STR(sraw(cur_exp->head), sraw(cur_real->head));
        cur_exp = (i < 2) ? cur_exp->children[0] : NULL;
        cur_real = (i < 2) ? cur_real->children[0] : NULL;
    }

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

/* in case when we have spaces from start of line */
CTEST(parse_precode_rule, correct_with_spaces_from_start)
{
    srand(time(NULL));
    String* str = screate("    ```\n");
    Array(Token) arr = tokenize(str);
    TNode* exp = init_tnode(NodePre, screate("<pre>"), NULL, true);
    TNode* exp_chd_lvl1 = init_tnode(NodeCode, screate("<code>"), NULL, true);
    TNode* exp_chd_lvl2 = init_tnode(NodeSpan, screate("<span>"), NULL, false);
    add_tnode(exp, exp_chd_lvl1);
    add_tnode(exp_chd_lvl1, exp_chd_lvl2);

    RulePerformer perf = {0};
    init_performer(&perf, arr, skip_spaces(0, arr));

    TNode* real = perf.invoke(&perf, perf.count);

    TNode* cur_exp = exp;
    TNode* cur_real = real;

    for (size_t i = 0; i < 3; ++i)
    {
        ASSERT_EQUAL(cur_exp->type, cur_real->type);
        ASSERT_STR(sraw(cur_exp->head), sraw(cur_real->head));
        cur_exp = (i < 2) ? cur_exp->children[0] : NULL;
        cur_real = (i < 2) ? cur_real->children[0] : NULL;
    }

    sfree(str);
    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

/* in case when we have spaces between tokens */
CTEST(parse_precode_rule, incorrect_with_spaces_between_tokens)
{
    srand(time(NULL));
    String* str = screate("    ``     `` ``\n");
    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, skip_spaces(0, arr));

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodePre, real->type);

    sfree(str);
    free_test_data(arr);
    free_tnode(real);
}
