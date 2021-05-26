#include "parse-single-rule-helper.h"
#include <ctest.h>

/* in case when we have correct rule */
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

/* in case when we have correct rule */
CTEST(parse_list_rule, ol_correct)
{
    srand(time(NULL));
    size_t len = rand() % 100 + 1;
    char* num = mem_alloc(len + 1);
    for (size_t i = 0; i < len; i++)
    {
        num[i] = (char)((rand() % 9 + 1) + '0');
    }
    num[len] = 0;
    String* str = create_string(num);
    str->concat(str, ". \n");

    TNode* exp = init_tnode(NodeOList, create_string("<ol>"), NULL, true);
    TNode* exp_chd_lvl1 = init_tnode(NodeListItem, create_string("<li>"), NULL, true);
    add_tnode(exp, exp_chd_lvl1);

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    // ol
    ASSERT_EQUAL(exp->type, real->type);
    ASSERT_STR(exp->head->text(exp->head), real->head->text(real->head));

    // li
    ASSERT_EQUAL(exp_chd_lvl1->type, real->children[0]->type);
    ASSERT_STR(exp_chd_lvl1->head->text(exp_chd_lvl1->head), real->children[0]->head->text(real->children[0]->head));

    free(num);
    str->free(str);
    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

/* in case when we have ol started from 0 */
CTEST(parse_list_rule, ol_incorrect_start_from_zero)
{
    String* str = create_string("0123456789. \n");

    TNode* exp = init_tnode(NodeOList, create_string("<ol>"), NULL, true);
    TNode* exp_chd_lvl1 = init_tnode(NodeListItem, create_string("<li>"), NULL, true);
    add_tnode(exp, exp_chd_lvl1);

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(exp->type, real->type);
    ASSERT_EQUAL(NodeSpan, real->type);
    ASSERT_STR("0123456789. ", real->content->text(real->content));

    str->free(str);
    free_test_data(arr);
    free_tnode(exp);
    free_tnode(real);
}

/* in case when we have more tokens than allowed */
CTEST(parse_list_rule, incorrect_many_tokens)
{
    srand(time(NULL));
    // ul
    char* raw_data = generate_sequence_of_terms((char[]){'*', '+', '-'}, 3, rand() % 100 + 2);
    String* str = create_string(raw_data);
    str->concat(str, " \n");

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodeUOList, real->type);

    free(raw_data);
    str->free(str);
    free_test_data(arr);
    free_tnode(real);

    // ol
    raw_data = mem_alloc(13);
    for (size_t i = 0; i < 12; i += 2)
    {
        raw_data[i] = (char)((rand() % 9 + 1) + '0');
        raw_data[i + 1] = '.';
    }
    raw_data[12] = 0;
    arr = create_test_data(raw_data);

    init_performer(&perf, arr, 0);

    real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodeOList, real->type);

    free_test_data(arr);
    free_tnode(real);
}