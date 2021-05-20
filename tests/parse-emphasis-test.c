#include "parse-single-rule-helper.h"
#include <ctest.h>

static TNode* create_emphasis_from_test_data(const char* test_data, size_t height)
{
    String* str = create_string("");

    for (size_t i = 0; i < height; ++i)
    {
        str->append(str, rand() % EMPHASIS_TERM.count ? '*' : '_');
    }
    str->concat(str, test_data);
    for (size_t i = 0; i < height; ++i)
    {
        str->append(str, rand() % EMPHASIS_TERM.count ? '*' : '_');
    }
    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* result = perf.invoke(&perf, perf.count);
    str->free(str);
    free_test_data(arr);

    return result;
}

CTEST(parse_emphasis_rule, strong)
{
    const char* content = "i'm bold";

    TNode* real = create_emphasis_from_test_data(content, 2);

    ASSERT_EQUAL(NodeEmphasis, real->type);
    ASSERT_STR("<strong>", real->head->text(real->head));
    ASSERT_STR(content, real->children[0]->content->text(real->children[0]->content));

    free_tnode(real);
}

CTEST(parse_emphasis_rule, em)
{
    const char* content = "i'm italic";

    TNode* real = create_emphasis_from_test_data(content, 1);

    ASSERT_EQUAL(NodeEmphasis, real->type);
    ASSERT_STR("<em>", real->head->text(real->head));
    ASSERT_STR(content, real->children[0]->content->text(real->children[0]->content));

    free_tnode(real);
}

CTEST(parse_emphasis_rule, strong_em)
{
    const char* content = "i'm bold italic";

    TNode* real = create_emphasis_from_test_data(content, 3);

    ASSERT_EQUAL(NodeEmphasis, real->type);
    ASSERT_STR("<strong>", real->head->text(real->head));
    ASSERT_STR("<em>", real->children[0]->head->text(real->children[0]->head));
    ASSERT_STR(content, real->children[0]->children[0]->content->text(real->children[0]->children[0]->content));

    free_tnode(real);
}

CTEST(parse_emphasis_rule, with_random_count)
{

    const char* content = "some text";

    size_t height = rand() % 100 + 1;

    TNode* real = create_emphasis_from_test_data(content, height);
    TNode* tmp = real;

    while (height > 1)
    {
        ASSERT_EQUAL(NodeEmphasis, tmp->type);
        ASSERT_STR("<strong>", tmp->head->text(tmp->head));
        tmp = tmp->children[0];
        height -= 2;
    }
    if (height == 1)
    {
        ASSERT_STR("<em>", tmp->head->text(tmp->head));
        tmp = tmp->children[0];
    }
    ASSERT_STR(content, tmp->content->text(tmp->content));

    free_tnode(real);
}

CTEST(parse_emphasis_rule, quantity_doesnt_match)
{
}