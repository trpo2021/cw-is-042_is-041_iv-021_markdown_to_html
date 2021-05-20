#include "parse-single-rule-helper.h"
#include <ctest.h>

static TNode* create_bq_from_test_data(char* data, const char* content_after)
{
    String* str = create_string(data);
    str->concat(str, content_after);

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* result = perf.invoke(&perf, perf.count);

    free(data);
    str->free(str);
    free_test_data(arr);

    return result;
}

/* in case when we have correct rule ( 1 <= x <= 15 ('>')) */
CTEST(parse_blockquote_rule, correct)
{
    TNode* real = create_bq_from_test_data(generate_sequence_of_terms((char[]){'>'}, 1, rand() % 15 + 1), " test\n");

    TNode* tmp = real;
    while (tmp->children)
    {
        ASSERT_EQUAL(NodeBlockquote, tmp->type);
        tmp = tmp->children[0];
    }

    free_tnode(real);
}

/* in case when we have spaces between blockquotes */
CTEST(parse_blockquote_rule, correct_with_spaces)
{
    char* raw_data = generate_sequence_of_terms((char[]){'>', ' '}, 2, rand() % 14 + 1);
    TNode* real = create_bq_from_test_data(raw_data, "> test\n");

    TNode* tmp = real;
    while (tmp->children)
    {
        ASSERT_EQUAL(NodeBlockquote, tmp->type);
        tmp = tmp->children[0];
    }

    free_tnode(real);
}

/* in case when we have line break after sequence */
CTEST(parse_blockquote_rule, unexpected_line_break)
{
    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){'>'}, 1, rand() % 15 + 1));

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);
    ASSERT_NOT_EQUAL(NodeBlockquote, real->type);

    free_test_data(arr);
    free_tnode(real);
}

/* in case when we have more than 15 blockquotes */
CTEST(parse_blockquote_rule, incorrect_many_tokens)
{
    char* raw_data = generate_sequence_of_terms((char[]){'>'}, 1, rand() % 100 + 16);

    TNode* real = create_bq_from_test_data(raw_data, "> test\n");
    ASSERT_NOT_EQUAL(NodeBlockquote, real->type);

    free_tnode(real);
}