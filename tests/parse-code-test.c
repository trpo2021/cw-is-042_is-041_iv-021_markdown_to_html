#include "parse-single-rule-helper.h"
#include <ctest.h>

/* in case when we have correct rule */
CTEST(parse_code_rule, random_count)
{
    srand(time(NULL));
    const char* code_content = "test";
    size_t count = rand() % 100 + 1;
    char* raw_data = generate_sequence_of_terms((char[]){'`'}, 1, count);

    String* str = create_string(raw_data);
    str->concat(str, code_content);
    for (size_t i = 0; i < count; ++i)
    {
        str->append(str, '`');
    }
    str->append(str, '\n');

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeInlineCode, real->type);
    ASSERT_STR("<code>", real->head->text(real->head));
    ASSERT_STR(code_content, real->children[0]->content->text(real->children[0]->content));

    free(raw_data);
    str->free(str);
    free_test_data(arr);
    free_tnode(real);
}

/* in case when we have '`' in code */
CTEST(parse_code_rule, contains_other_tokens_in_code)
{
    srand(time(NULL));
    String* code_content = create_string("test");
    size_t count = rand() % 100 + 2;
    char* raw_data = generate_sequence_of_terms((char[]){'`'}, 1, count);

    String* str = create_string(raw_data);
    char* contained = malloc(count);
    for (size_t i = 0; i < count - 1; ++i)
    {
        contained[i] = '`';
    }
    contained[count - 1] = 0;

    code_content->insert(code_content, contained, (rand() % (sizeof(code_content) / 2 - 1) + 1));
    str->concat(str, code_content->text(code_content));
    for (size_t i = 0; i < count; ++i)
    {
        str->append(str, '`');
    }
    str->append(str, '\n');

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeInlineCode, real->type);
    ASSERT_STR("<code>", real->head->text(real->head));
    ASSERT_STR(code_content->text(code_content), real->children[0]->content->text(real->children[0]->content));

    free(contained);
    free(raw_data);
    str->free(str);
    code_content->free(code_content);
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
    ASSERT_STR("<span>", real->head->text(real->head));
    // 1 cuz without balance
    ASSERT_STR("`", real->content->text(real->content));

    free_test_data(arr);
    free_tnode(real);
}