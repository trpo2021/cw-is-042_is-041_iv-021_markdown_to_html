#include <internals/parser/parser.h>

typedef enum
{
    /* used for words, numbers and chars, that don't match */
    StateText,
    /* used for single char tokens */
    StateOther
} LState;

static int is_match(char c)
{
    char tokens[] = "_\n*+-#\t \\`!=[]()<>";
    for (int i = 0; i < sizeof(tokens); i++)
    {
        if (tokens[i] == c)
            return i;
    }
    return -1;
}

static LState get_lstate(string raw, int index)
{
    if (is_match(raw->Get(raw, index)) > -1)
        return StateOther;
    return StateText;
}

collection(Token_t) Tokenize(const string raw)
{
    collection(Token_t) vector = NULL;
    LState state = get_lstate(raw, 0);
    string value = init(10);
    for (int i = 0; i < raw->Length(raw); i++)
    {
        char c = raw->Get(raw, i);
        switch (state)
        {
        case StateText:
        {
            if (is_match(c) == -1)
            {
                value->Append(value, c);
            }
            else
            {
                Token_t token = {.type = TypeText, .value = value->Copy(value)};
                collection_add(vector, token);
                value->Clear(value);
                state = get_lstate(raw, i);
                --i;
            }
        }
        break;
        case StateOther:
        {
            if (is_match(c) == -1)
            {
                value->Clear(value);
                state = get_lstate(raw, i);
                --i;
            }
            else
            {
                value->Append(value, c);
                Token_t token = {.type = (TokenType)(is_match(c)), .value = value->Copy(value)};
                collection_add(vector, token);
                value->Clear(value);
            }
        }
        break;
        }
    }
    value->Free(value);
    return vector;
}
