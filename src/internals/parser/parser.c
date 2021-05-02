#include <ctype.h>
#include <internals/parser/parser.h>
#include <stdio.h>

typedef enum
{
    /* used for words, numbers and chars, that don't match */
    StateText,
    /* used for single char tokens */
    StateOther
} LState;

/* return index of char in token values array if match, else return -1 */
int char_is_match(char c)
{
    char tokens[] = "_\n*+-#\t \\`!=[]()<>";
    for (int i = 0; i < sizeof(tokens); i++)
    {
        if (tokens[i] == c)
            return i;
    }
    return -1;
}

LState get_lstate(string raw, int index)
{
    if (char_is_match(raw->Get(raw, index)) > -1)
        return StateOther;
    return StateText;
}

/* return collection of tokens, make sure, that you free every token value, before collection_free */
collection(Token_t) tokenize(const string raw)
{
    collection(Token_t) vector = NULL;
    LState state = get_lstate(raw, 0);
    /* temp container */
    string value = init(10);
    for (int i = 0; i < raw->Length(raw); i++)
    {
        char c = raw->Get(raw, i);
        switch (state)
        {
        case StateText:
        {
            /* if tokens don't contains this char */
            if (char_is_match(c) == -1)
            {
                /* just value += c */
                value->Append(value, c);
            }
            else
            {
                /* create token from value and context */
                Token_t token = {.type = TypeText, .value = value->Copy(value)};
                /* add to collection */
                collection_add(vector, token);
                /* we're done with this token, need to clear container */
                value->Clear(value);
                state = get_lstate(raw, i);
                --i;
            }
        }
        break;
        case StateOther:
        {
            /* if tokens don't contains this char */
            if (char_is_match(c) == -1)
            {
                /* we're done with this token, need to clear container */
                value->Clear(value);
                state = get_lstate(raw, i);
                --i;
            }
            else
            {
                /* just value += c */
                value->Append(value, c);
                /* create token from value and context */
                /* to get type -> find char's index in token array */
                /* +1 cuz of first constant TypeText, may be i should put it in the end */
                Token_t token = {.type = (TokenType)(char_is_match(c)), .value = value->Copy(value)};
                /* add to collection */
                collection_add(vector, token);
                /* we're done with this token, need to clear container */
                value->Clear(value);
            }
        }
        break;
        }
    }
    /* here need to check value in case, when text in the end of string */
    /* but i think to use \n in the end of every string */
    /* delete temp container */
    value->Free(value);
    return vector;
}