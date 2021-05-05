#include <ctest.h>
#include <internals/parser/collection.h>
#include <internals/parser/parser.h>
#include <stdio.h>

CTEST(tokenizer, get_token_value)
{
    string str = create("1. # some. *italic*.   text\n");
    collection(Token_t) vec = Tokenize(str);
    ASSERT_STR("1.", vec[0].value->Text(vec[0].value));
    ASSERT_STR(" ", vec[1].value->Text(vec[1].value));
    ASSERT_STR("#", vec[2].value->Text(vec[2].value));
    ASSERT_STR(" ", vec[3].value->Text(vec[3].value));
    ASSERT_STR("some.", vec[4].value->Text(vec[4].value));
    ASSERT_STR(" ", vec[5].value->Text(vec[5].value));
    ASSERT_STR("*", vec[6].value->Text(vec[6].value));
    ASSERT_STR("italic", vec[7].value->Text(vec[7].value));
    ASSERT_STR("*", vec[8].value->Text(vec[8].value));
    ASSERT_STR(".", vec[9].value->Text(vec[9].value));
    ASSERT_STR(" ", vec[10].value->Text(vec[10].value));
    ASSERT_STR(" ", vec[11].value->Text(vec[11].value));
    ASSERT_STR(" ", vec[12].value->Text(vec[12].value));
    ASSERT_STR("text", vec[13].value->Text(vec[13].value));
    ASSERT_STR("\n", vec[14].value->Text(vec[14].value));
    for (size_t i = 0; i < collection_get_size(vec); i++)
    {
        vec[i].value->Free(vec[i].value);
    }
    collection_free(vec);
    str->Free(str);
}

CTEST(tokenizer, get_token_type)
{
    string str = create("1. # some. *italic*.   text\n");
    collection(Token_t) vec = Tokenize(str);
    ASSERT_EQUAL(TypeText, vec[0].type);
    ASSERT_EQUAL(TypeSpace, vec[1].type);
    ASSERT_EQUAL(TypeLattice, vec[2].type);
    ASSERT_EQUAL(TypeSpace, vec[3].type);
    ASSERT_EQUAL(TypeText, vec[4].type);
    ASSERT_EQUAL(TypeSpace, vec[5].type);
    ASSERT_EQUAL(TypeAsterisk, vec[6].type);
    ASSERT_EQUAL(TypeText, vec[7].type);
    ASSERT_EQUAL(TypeAsterisk, vec[8].type);
    ASSERT_EQUAL(TypeText, vec[9].type);
    ASSERT_EQUAL(TypeSpace, vec[10].type);
    ASSERT_EQUAL(TypeSpace, vec[11].type);
    ASSERT_EQUAL(TypeSpace, vec[12].type);
    ASSERT_EQUAL(TypeText, vec[13].type);
    ASSERT_EQUAL(TypeLineBreak, vec[14].type);
    for (size_t i = 0; i < collection_get_size(vec); i++)
    {
        vec[i].value->Free(vec[i].value);
    }
    collection_free(vec);
    str->Free(str);
}

CTEST(tokenizer, token_type_to_string)
{
    string str = create("1. # some. *italic*.   text\n");
    collection(Token_t) vec = Tokenize(str);
    ASSERT_STR("TypeText", GET_TOKEN_NAME(vec[0].type));
    ASSERT_STR("TypeSpace", GET_TOKEN_NAME(vec[1].type));
    ASSERT_STR("TypeLattice", GET_TOKEN_NAME(vec[2].type));
    ASSERT_STR("TypeSpace", GET_TOKEN_NAME(vec[3].type));
    ASSERT_STR("TypeText", GET_TOKEN_NAME(vec[4].type));
    ASSERT_STR("TypeSpace", GET_TOKEN_NAME(vec[5].type));
    ASSERT_STR("TypeAsterisk", GET_TOKEN_NAME(vec[6].type));
    ASSERT_STR("TypeText", GET_TOKEN_NAME(vec[7].type));
    ASSERT_STR("TypeAsterisk", GET_TOKEN_NAME(vec[8].type));
    ASSERT_STR("TypeText", GET_TOKEN_NAME(vec[9].type));
    ASSERT_STR("TypeSpace", GET_TOKEN_NAME(vec[10].type));
    ASSERT_STR("TypeSpace", GET_TOKEN_NAME(vec[11].type));
    ASSERT_STR("TypeSpace", GET_TOKEN_NAME(vec[12].type));
    ASSERT_STR("TypeText", GET_TOKEN_NAME(vec[13].type));
    ASSERT_STR("TypeLineBreak", GET_TOKEN_NAME(vec[14].type));
    for (size_t i = 0; i < collection_get_size(vec); i++)
    {
        vec[i].value->Free(vec[i].value);
    }
    collection_free(vec);
    str->Free(str);
}

CTEST(tokenizer, check_all_tokens)
{
    string str = create("_\n*+-#\t \\`!=[]()<>");
    collection(Token_t) vec = Tokenize(str);
    for (size_t i = 0; i < collection_get_size(vec); i++)
    {
        ASSERT_STR(EnumToString[i], GET_TOKEN_NAME(vec[i].type));
        ASSERT_EQUAL((TokenType)i, vec[i].type);
        char* tmp = malloc(2);
        tmp[0] = (str->Get(str, i));
        tmp[1] = '\0';
        ASSERT_STR(tmp, vec[i].value->Text(vec[i].value));
        free(tmp);
        vec[i].value->Free(vec[i].value);
    }
    collection_free(vec);
    str->Free(str);
}