#include "parse-single-rule-helper.h"
#include <ctest.h>

CTEST(parse_img_rule, default_usage)
{
    String* str = screate("![]()");

    Array(Token) arr = tokenize(str);

    RulePerformer perf = {0};
    init_performer(&perf, arr, 0);

    TNode* real = perf.invoke(&perf, perf.count);

    ASSERT_EQUAL(NodeImage, real->type);
    ASSERT_STR("<img>", sraw(real->head));

    sfree(str);
    free_test_data(arr);
    free_tnode(real);
}