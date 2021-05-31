#include <ctest.h>
#include <internals/collection/collection.h>
#include <internals/parser/helpers/rule-performer.h>
#include <internals/parser/lexer/tokenizer.h>

CTEST(rp_help, skip_spaces_skip_case)
{
    String* str = screate("   start from 3\n");
    Array(Token) arr = tokenize(str);

    ASSERT_EQUAL(3, skip_spaces(0, arr));

    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        sfree(arr[i].value);
    }
    free_array(arr);
    sfree(str);
}

CTEST(rp_help, skip_spaces_wo_spaces_case)
{
    String* str = screate("start from zero\n");
    Array(Token) arr = tokenize(str);

    ASSERT_EQUAL(0, skip_spaces(0, arr));

    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        sfree(arr[i].value);
    }
    free_array(arr);
    sfree(str);
}