#include "parse-single-rule-helper.h"
#include <ctest.h>
#include <time.h>

CTEST(parse_list_rule, ul_correct)
{
    srand(time(NULL));
    char* raw_data = generate_sequence_of_terms((char[]){'*', '+', '-'}, 3, 1);
    String* str = create_string(raw_data);
    str->concat(str, " \n");

    TNode* exp = init_tnode(NodeUOList, create_string("<ul>"), NULL, true);
    TNode* exp_chd_lvl1 = init_tnode(NodeListItem, create_string("<li>"), NULL, true);
    add_tnode(exp, exp_chd_lvl1);

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    // ul
    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(exp->head->text(exp->head), real->head->text(real->head));

    // li
    ASSERT_EQUAL(exp_chd_lvl1->type, real->children[0]->type);
    ASSERT_STR(exp_chd_lvl1->head->text(exp_chd_lvl1->head), real->children[0]->head->text(real->children[0]->head));

    free(raw_data);
    str->free(str);
    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

CTEST(parse_list_rule, ul_incorrect_many_tokens)
{
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){'*', '+', '-'}, 3, rand() % 100 + 2));

    free_test_data(arr);
}
