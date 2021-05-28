#include "parse-single-rule-helper.h"
#include <ctest.h>

/* in case when we have correct rule */
CTEST(parse_code_rule, random_count)
{
    srand(time(NULL));
    const char* code_content = "test";
    size_t count = rand() % 100 + 1;
    char* raw_data = generate_sequence_of_terms((char[]){'`'}, 1, count);

    String* str = screate(raw_data);
    sconcat(str, code_content);
    for (size_t i = 0; i < count; ++i)
    {
        sappend(str, '`');
    }
    sappend(str, '\n');

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeInlineCode, real->type);
    ASSERT_STR("<code>", sraw(real->head));
    ASSERT_STR(code_content, sraw(real->children[0]->content));

    free(raw_data);
    sfree(str);
    free_test_data(arr);
    free_tnode(real);
}

/* in case when we have '`' in code */
CTEST(parse_code_rule, contains_other_tokens_in_code)
{
    srand(time(NULL));
    String* code_content = screate("test");
    size_t count = rand() % 100 + 2;
    char* raw_data = generate_sequence_of_terms((char[]){'`'}, 1, count);

    String* str = screate(raw_data);
    char* contained = mem_alloc(count);
    for (size_t i = 0; i < count - 1; ++i)
    {
        contained[i] = '`';
    }
    contained[count - 1] = 0;

    sinsert(code_content, contained, (rand() % (sizeof(code_content) / 2 - 1) + 1));
    sconcat(str, sraw(code_content));
    for (size_t i = 0; i < count; ++i)
    {
        sappend(str, '`');
    }
    sappend(str, '\n');

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeInlineCode, real->type);
    ASSERT_STR("<code>", sraw(real->head));
    ASSERT_STR(sraw(code_content), sraw(real->children[0]->content));

    free(contained);
    free(raw_data);
    sfree(str);
    sfree(code_content);
    free_test_data(arr);
    free_tnode(real);
}

/* in case when we have code without content */
CTEST(parse_code_rule, content_empty)
{
    srand(time(NULL));

    Array(Token) arr = create_test_data(generate_sequence_of_terms((char[]){'`'}, 1, 2));

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_NOT_EQUAL(NodeInlineCode, real->type);
    ASSERT_STR("<span>", sraw(real->head));
    ASSERT_STR("`", sraw(real->content));

    free_test_data(arr);
    free_tnode(real);
}