#include "parse-single-rule-helper.h"
#include <ctest.h>

CTEST(parse_img_rule, default_usage)
{
    String* str = create_string("![]()");

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeImage, real->type);
    ASSERT_STR("<img>", real->head->text(real->head));

    str->free(str);
    free_test_data(arr);
    free_tnode(real);
}