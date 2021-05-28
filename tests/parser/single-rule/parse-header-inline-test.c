#include "parse-single-rule-helper.h"
#include <ctest.h>

static TNode* create_header_from_test_data(char* raw_data, const char* content_after, size_t count)
{
    String* str = screate(raw_data);
    sconcat(str, content_after);

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* result = perf.invoke(&perf, perf.count);

    free(raw_data);
    sfree(str);
    free_test_data(arr);

    return result;
}

/* in case when we have correct rule ( 1 <= x <= 6 ('#')) */
CTEST(parse_header_inline_rule, correct)
{
    size_t count = rand() % 6 + 1;

    String* exp_head = screate("<h");
    sappend(exp_head, (char)(count + '0'));
    sappend(exp_head, '>');

    char* raw_data = generate_sequence_of_terms((char[]){'#'}, 1, count);

    TNode* real = create_header_from_test_data(raw_data, " test\n", count);

    ASSERT_EQUAL(NodeHeadingInline, real->type);
    ASSERT_STR(sraw(exp_head), sraw(real->head));

    sfree(exp_head);
    free_tnode(real);
}

/* in case when we have more tokens than 6 */
CTEST(parse_header_inline_rule, incorrect_many_tokens)
{
    size_t count = rand() % 100 + 7;

    char* raw_data = generate_sequence_of_terms((char[]){'#'}, 1, count);

    TNode* real = create_header_from_test_data(raw_data, " test\n", count);

    ASSERT_NOT_EQUAL(NodeHeadingInline, real->type);

    free_tnode(real);
}

/* in case when we don't have space after sequence */
CTEST(parse_header_inline_rule, incorrect_header_merged)
{
    size_t count = rand() % 7 + 1;

    char* raw_data = generate_sequence_of_terms((char[]){'#'}, 1, count);

    TNode* real = create_header_from_test_data(raw_data, "test\n", count);

    ASSERT_NOT_EQUAL(NodeHeadingInline, real->type);

    free_tnode(real);
}