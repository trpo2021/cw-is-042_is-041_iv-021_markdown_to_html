#include <ctest.h>
#include <internals/parser/lexer/tokenizer.h>
#include <stdio.h>
#include <time.h>

static String* convert_to_string(size_t num)
{
    char* buf = NULL;
    size_t len;
    convert_to_char_array(buf, num, "%zu", len);
    String* out = screate(buf);
    free(buf);
    return out;
}

CTEST(tokenizer, check_long_number)
{
    srand(time(NULL));
    String* str = convert_to_string(rand() % 100000000 + 10000000);
    sconcat(str, ".\n");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(TokenNumber, arr[0].type);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        sfree(arr[i].value);
    }
    free_array(arr);
    sfree(str);
}

CTEST(tokenizer, check_empty)
{
    String* str = screate("");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(0, get_array_length(arr));
    free_array(arr);
    sfree(str);
}

CTEST(tokenizer, try_valid_number)
{
    String* str = screate("1. 2. 3. 4. 5. 6. 7. 8. 9. 123456. ");
    Array(Token) arr = tokenize(str);
    for (size_t i = 0; i < get_array_length(arr); i += 2)
    {
        ASSERT_EQUAL(TokenNumber, arr[i].type);
        sfree(arr[i].value);
        sfree(arr[i + 1].value);
    }
    free_array(arr);
    sfree(str);
}

CTEST(tokenizer, try_invalid_number)
{
    String* str = screate("012.\n");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(TokenText, arr[0].type);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        sfree(arr[i].value);
    }
    free_array(arr);
    sfree(str);
}

CTEST(tokenizer, escape_number)
{
    String* str = screate("\\1.\n");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(TokenText, arr[0].type);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        sfree(arr[i].value);
    }
    free_array(arr);
    sfree(str);
}

CTEST(tokenizer, escape_escape)
{
    String* str = screate("\\\\\n");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(TokenText, arr[0].type);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        sfree(arr[i].value);
    }
    free_array(arr);
    sfree(str);
}

CTEST(tokenizer, escape_all_single_tokens)
{
    String* str = screate("\\\n\\_\\*\\`\\=\\-\\+\\<\\#\\!\\[\\>\\ \\]\\(\\)");
    Array(Token) arr = tokenize(str);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        ASSERT_EQUAL(TokenText, arr[0].type);
        sfree(arr[i].value);
    }
    free_array(arr);
    sfree(str);
}

CTEST(tokenizer, check_all_single_tokens)
{
    String* str = screate("\n_*`=-+<#![> ]()");
    Array(Token) arr = tokenize(str);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        ASSERT_EQUAL(sget(str, i), sget(arr[i].value, 0));
        ASSERT_EQUAL((TypeOfToken)i, arr[i].type);
        i < TokenSpace ? ASSERT_TRUE(arr[i].op) : ASSERT_FALSE(arr[i].op);
        sfree(arr[i].value);
    }
    free_array(arr);
    sfree(str);
}

CTEST(tokenizer, ascii_table_to_token_text)
{
    String* str = screate("\"$%&',./0123456789:;?@QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm^~|\n");
    Array(Token) arr = tokenize(str);
    ASSERT_EQUAL(2, get_array_length(arr));
    ASSERT_EQUAL(TokenText, arr[0].type);
    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        sfree(arr[i].value);
    }
    free_array(arr);
    sfree(str);
}