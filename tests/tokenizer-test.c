#include <ctest.h>
#include <internals/parser/collection.h>
#include <internals/parser/parser.h>
#include <time.h>

static string convert_to_string(size_t num)
{
    char* buf = NULL;
    size_t len;
    ToCharArray(buf, num, "%zu", len);
    string out = create(buf);
    free(buf);
    return out;
}

CTEST(tokenizer, check_long_number)
{
    srand(time(NULL));
    string str = convert_to_string(rand() % 100000000 + 10000000);
    str->Concat(str, ".\n");
    ArrayList(Token) list = Tokenize(str);
    ASSERT_EQUAL(TokenNumber, list[0].type);
    for (size_t i = 0; i < ArrayListGetLength(list); ++i)
    {
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, check_empty)
{
    string str = create("");
    ArrayList(Token) list = Tokenize(str);
    ASSERT_EQUAL(0, ArrayListGetLength(list));
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, try_valid_number)
{
    string str = create("1. 2. 3. 4. 5. 6. 7. 8. 9. 123456. ");
    ArrayList(Token) list = Tokenize(str);
    for (size_t i = 0; i < ArrayListGetLength(list); i += 2)
    {
        ASSERT_EQUAL(TokenNumber, list[i].type);
        list[i].value->Free(list[i].value);
        list[i + 1].value->Free(list[i + 1].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, try_invalid_number)
{
    string str = create("012.\n");
    ArrayList(Token) list = Tokenize(str);
    ASSERT_EQUAL(TokenText, list[0].type);
    for (size_t i = 0; i < ArrayListGetLength(list); ++i)
    {
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, escape_number)
{
    string str = create("\\1.\n");
    ArrayList(Token) list = Tokenize(str);
    ASSERT_EQUAL(TokenText, list[0].type);
    for (size_t i = 0; i < ArrayListGetLength(list); ++i)
    {
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, escape_escape)
{
    string str = create("\\\\\n");
    ArrayList(Token) list = Tokenize(str);
    ASSERT_EQUAL(TokenText, list[0].type);
    for (size_t i = 0; i < ArrayListGetLength(list); ++i)
    {
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, escape_all_single_tokens)
{
    string str = create("\\\n\\_\\*\\`\\=\\-\\+\\<\\#\\!\\[\\>\\ \\]\\(\\)");
    ArrayList(Token) list = Tokenize(str);
    for (size_t i = 0; i < ArrayListGetLength(list); ++i)
    {
        ASSERT_EQUAL(TokenText, list[0].type);
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, check_all_single_tokens)
{
    string str = create("\n_*`=-+<#![> ]()");
    ArrayList(Token) list = Tokenize(str);
    for (size_t i = 0; i < ArrayListGetLength(list); ++i)
    {
        ASSERT_EQUAL(str->Get(str, i), TokenToCharArray(list[i])[0]);
        ASSERT_EQUAL((TypeOfToken)i, list[i].type);
        i < TokenSpace ? ASSERT_TRUE(list[i].op) : ASSERT_FALSE(list[i].op);
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, ascii_table_to_token_text)
{
    string str = create("\"$%&',./0123456789:;?@QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm^~|\n");
    ArrayList(Token) list = Tokenize(str);
    ASSERT_EQUAL(2, ArrayListGetLength(list));
    ASSERT_EQUAL(TokenText, list[0].type);
    for (size_t i = 0; i < ArrayListGetLength(list); ++i)
    {
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}