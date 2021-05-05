#include <ctest.h>
#include <internals/parser/collection.h>
#include <internals/parser/parser.h>
#include <stdio.h>

CTEST(tokenizer, get_token_value)
{
    string str = create("1. # some. *italic*.   text\n");
    ArrayList(Token) list = Tokenize(str);
    ASSERT_STR("1.", list[0].value->Text(list[0].value));
    ASSERT_STR(" ", list[1].value->Text(list[1].value));
    ASSERT_STR("#", list[2].value->Text(list[2].value));
    ASSERT_STR(" ", list[3].value->Text(list[3].value));
    ASSERT_STR("some.", list[4].value->Text(list[4].value));
    ASSERT_STR(" ", list[5].value->Text(list[5].value));
    ASSERT_STR("*", list[6].value->Text(list[6].value));
    ASSERT_STR("italic", list[7].value->Text(list[7].value));
    ASSERT_STR("*", list[8].value->Text(list[8].value));
    ASSERT_STR(".", list[9].value->Text(list[9].value));
    ASSERT_STR(" ", list[10].value->Text(list[10].value));
    ASSERT_STR(" ", list[11].value->Text(list[11].value));
    ASSERT_STR(" ", list[12].value->Text(list[12].value));
    ASSERT_STR("text", list[13].value->Text(list[13].value));
    ASSERT_STR("\n", list[14].value->Text(list[14].value));
    for (size_t i = 0; i < ArrayListGetLength(list); i++)
    {
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, get_token_type)
{
    string str = create("1. # some. *italic*.   text\n");
    ArrayList(Token) list = Tokenize(str);
    ASSERT_EQUAL(TokenText, list[0].type);
    ASSERT_EQUAL(TokenSpace, list[1].type);
    ASSERT_EQUAL(TokenLattice, list[2].type);
    ASSERT_EQUAL(TokenSpace, list[3].type);
    ASSERT_EQUAL(TokenText, list[4].type);
    ASSERT_EQUAL(TokenSpace, list[5].type);
    ASSERT_EQUAL(TokenAsterisk, list[6].type);
    ASSERT_EQUAL(TokenText, list[7].type);
    ASSERT_EQUAL(TokenAsterisk, list[8].type);
    ASSERT_EQUAL(TokenText, list[9].type);
    ASSERT_EQUAL(TokenSpace, list[10].type);
    ASSERT_EQUAL(TokenSpace, list[11].type);
    ASSERT_EQUAL(TokenSpace, list[12].type);
    ASSERT_EQUAL(TokenText, list[13].type);
    ASSERT_EQUAL(TokenLineBreak, list[14].type);
    for (size_t i = 0; i < ArrayListGetLength(list); i++)
    {
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, token_type_to_string)
{
    string str = create("1. # some. *italic*.   text\n");
    ArrayList(Token) list = Tokenize(str);
    ASSERT_STR("TokenText", TokenToString(list[0].type));
    ASSERT_STR("TokenSpace", TokenToString(list[1].type));
    ASSERT_STR("TokenLattice", TokenToString(list[2].type));
    ASSERT_STR("TokenSpace", TokenToString(list[3].type));
    ASSERT_STR("TokenText", TokenToString(list[4].type));
    ASSERT_STR("TokenSpace", TokenToString(list[5].type));
    ASSERT_STR("TokenAsterisk", TokenToString(list[6].type));
    ASSERT_STR("TokenText", TokenToString(list[7].type));
    ASSERT_STR("TokenAsterisk", TokenToString(list[8].type));
    ASSERT_STR("TokenText", TokenToString(list[9].type));
    ASSERT_STR("TokenSpace", TokenToString(list[10].type));
    ASSERT_STR("TokenSpace", TokenToString(list[11].type));
    ASSERT_STR("TokenSpace", TokenToString(list[12].type));
    ASSERT_STR("TokenText", TokenToString(list[13].type));
    ASSERT_STR("TokenLineBreak", TokenToString(list[14].type));
    for (size_t i = 0; i < ArrayListGetLength(list); i++)
    {
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}

CTEST(tokenizer, check_all_tokens)
{
    string str = create("_\n*+-#\t \\`!=[]()<>");
    ArrayList(Token) list = Tokenize(str);
    for (size_t i = 0; i < ArrayListGetLength(list); i++)
    {
        ASSERT_STR(TOKEN_TO_STRING[i], TokenToString(list[i].type));
        ASSERT_EQUAL((TypeOfToken)i, list[i].type);
        char* tmp = malloc(2);
        tmp[0] = (str->Get(str, i));
        tmp[1] = '\0';
        ASSERT_STR(tmp, list[i].value->Text(list[i].value));
        free(tmp);
        list[i].value->Free(list[i].value);
    }
    ArrayListFree(list);
    str->Free(str);
}