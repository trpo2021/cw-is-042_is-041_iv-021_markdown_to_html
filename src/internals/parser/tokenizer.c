#include <internals/parser/parser.h>

#define NOT_FOUND_CODE -1

static const char tokens[] = "\n_*`=-+<#![> ]()";

typedef enum
{
    /* used for words, numbers and chars, that don't match */
    StateText,
    /* for escape */
    StateEscape,
    /* used for single char tokens */
    StateOther
} LState;

static int8_t is_match(char c)
{
    for (int8_t i = 0; i < sizeof(tokens); ++i)
    {
        if (tokens[i] == c)
        {
            return i;
        }
    }
    return NOT_FOUND_CODE;
}

/* valid: 123. or something like this */

static TypeOfToken validate_number(const string value)
{
    const char* text = value->Text(value);
    if (text[0] >= '1' && text[0] <= '9')
    {
        size_t i = 1;
        for (; i < value->Length(value) - 1; ++i)
        {
            if (text[i] < '0' || text[i] > '9')
            {
                return TokenText;
            }
        }
        if (text[i] == '.')
        {
            return TokenNumber;
        }
    }
    return TokenText;
}

static LState get_lstate(const string line, size_t index)
{
    if (is_match(line->Get(line, index)) == NOT_FOUND_CODE)
    {
        return StateText;
    }
    return StateOther;
}

ArrayList(Token) Tokenize(const string line)
{
    ArrayList(Token) list = NULL;
    LState state = get_lstate(line, 0);
    string value = init(10);
    for (size_t i = 0; i < line->Length(line); ++i)
    {
        char c = line->Get(line, i);
        if (c == '\\' && i + 2 < line->Length(line) && state != StateEscape)
        {
            state = StateEscape;
            continue;
        }
        switch (state)
        {
        case StateText:
        {
            if (is_match(c) == NOT_FOUND_CODE)
            {
                value->Append(value, c);
            }
            else
            {
                Token token = {.type = validate_number(value), .value = value->Copy(value)};
                token.op = token.type == TokenNumber ? true : false;
                ArrayListAdd(list, token);
                value->Clear(value);
                state = get_lstate(line, i);
                --i;
            }
        }
        break;
        case StateOther:
        {
            if (is_match(c) == NOT_FOUND_CODE)
            {
                value->Clear(value);
                state = get_lstate(line, i);
                --i;
            }
            else
            {
                value->Append(value, c);
                Token token = {.type = (TypeOfToken)(is_match(c)), .value = value->Copy(value)};
                token.op = token.type < TokenSpace ? true : false;
                ArrayListAdd(list, token);
                value->Clear(value);
            }
        }
        break;
        case StateEscape:
        {
            value->Append(value, c);
            Token token = {.type = TokenText, .value = value->Copy(value), false};
            ArrayListAdd(list, token);
            value->Clear(value);
            state = get_lstate(line, i + 1);
        }
        break;
        }
    }
    value->Free(value);
    return list;
}
