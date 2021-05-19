#include "parse-single-rule-helper.h"
#include <ctest.h>
#include <time.h>

CTEST(parse_precode_rule, rule_precode_correct)
{
    srand(time(NULL));
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){'`'}, 1, rand() % 100 + 3));
    TNode* exp = init_tnode(NodePre, create_string("<pre>"), NULL, true);
    TNode* exp_chd_lvl1 = init_tnode(NodeCode, create_string("<code>"), NULL, true);
    TNode* exp_chd_lvl2 = init_tnode(NodeSpan, create_string("<span>"), NULL, false);
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
        ASSERT_STR(cur_exp->head->text(cur_exp->head), cur_real->head->text(cur_real->head));
        cur_exp = (i < 2) ? cur_exp->children[0] : NULL;
        cur_real = (i < 2) ? cur_real->children[0] : NULL;
    }

    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

CTEST(parse_precode_rule, rule_precode_correct_with_spaces_from_start)
{
    srand(time(NULL));
    String* str = create_string("    ```\n");
    Array(Token) arr = tokenize(str);
    TNode* exp = init_tnode(NodePre, create_string("<pre>"), NULL, true);
    TNode* exp_chd_lvl1 = init_tnode(NodeCode, create_string("<code>"), NULL, true);
    TNode* exp_chd_lvl2 = init_tnode(NodeSpan, create_string("<span>"), NULL, false);
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
        ASSERT_STR(cur_exp->head->text(cur_exp->head), cur_real->head->text(cur_real->head));
        cur_exp = (i < 2) ? cur_exp->children[0] : NULL;
        cur_real = (i < 2) ? cur_real->children[0] : NULL;
    }

    str->free(str);
    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}
