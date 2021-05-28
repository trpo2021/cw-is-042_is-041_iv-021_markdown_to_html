#include <internals/collection/collection.h>
#include <internals/parser/lexer/tokenizer.h>
#include <inttypes.h>

typedef enum
{
    NOT_FOUND_CODE = -1
} LexerConstants;

static const char tokens[] = "\n_*`=-+<#![> ]()";

typedef enum
{
    StateText,
    StateEscape,
    StateOther
} LState;

/******************************
 *                            *
 *  Section: Helper functions *
 *                            *
 ******************************/

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

static TypeOfToken validate_number(const String* value)
{
    const char* text = sraw(value);
    if (text[0] >= '1' && text[0] <= '9')
    {
        size_t i = 1;
        for (; i < slength(value) - 1; ++i)
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

static LState get_lstate(const String* line, size_t index)
{
    if (is_match(sget(line, index)) == NOT_FOUND_CODE)
    {
        return StateText;
    }
    return StateOther;
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/

/******************************
 *                            *
 *    Section: Main lexer     *
 *                            *
 ******************************/

Token* tokenize(const String* line)
{
    Token* arr = NULL;
    LState state = get_lstate(line, 0);
    String* value = sinit(10);

    for (size_t i = 0; i < slength(line); ++i)
    {
        char c = sget(line, i);
        if (c == '\\' && i + 2 < slength(line) && state != StateEscape)
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
                sappend(value, c);
            }
            else
            {
                Token token = {.type = validate_number(value), .value = scopy(value)};
                token.op = token.type == TokenNumber ? true : false;
                add_array_item(arr, token);
                sclear(value);
                state = get_lstate(line, i);
                --i;
            }
        }
        break;
        case StateOther:
        {
            if (is_match(c) == NOT_FOUND_CODE)
            {
                sclear(value);
                state = get_lstate(line, i);
                --i;
            }
            else
            {
                sappend(value, c);
                Token token = {.type = (TypeOfToken)(is_match(c)), .value = scopy(value)};
                token.op = token.type < TokenSpace ? true : false;
                add_array_item(arr, token);
                sclear(value);
            }
        }
        break;
        case StateEscape:
        {
            sappend(value, c);
            Token token = {.type = TokenText, .value = scopy(value), false};
            add_array_item(arr, token);
            sclear(value);
            state = get_lstate(line, i + 1);
        }
        break;
        }
    }

    sfree(value);
    return arr;
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/