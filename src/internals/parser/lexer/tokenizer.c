#include <internals/parser/main/parser.h>

#define NOT_FOUND_CODE -1

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

/* if single tokens contains symbol */
/* @param c symbol for check */
/* @return index in array of tokens or NOT_FOUND_CODE */
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

/* validate text to numer, valid: 123. or something like this */
/* @param value token content */
/* @return TokenNumber if valid, else TokenText */
static TypeOfToken validate_number(const String* value)
{
    const char* text = value->text(value);
    if (text[0] >= '1' && text[0] <= '9')
    {
        size_t i = 1;
        for (; i < value->length(value) - 1; ++i)
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
    if (is_match(line->get(line, index)) == NOT_FOUND_CODE)
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

Array(Token) tokenize(const String* line)
{
    Array(Token) arr = NULL;
    LState state = get_lstate(line, 0);
    String* value = init_string(10);
    for (size_t i = 0; i < line->length(line); ++i)
    {
        char c = line->get(line, i);
        if (c == '\\' && i + 2 < line->length(line) && state != StateEscape)
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
                value->append(value, c);
            }
            else
            {
                Token token = {.type = validate_number(value), .value = value->copy(value)};
                token.op = token.type == TokenNumber ? true : false;
                add_array_item(arr, token);
                value->clear(value);
                state = get_lstate(line, i);
                --i;
            }
        }
        break;
        case StateOther:
        {
            if (is_match(c) == NOT_FOUND_CODE)
            {
                value->clear(value);
                state = get_lstate(line, i);
                --i;
            }
            else
            {
                value->append(value, c);
                Token token = {.type = (TypeOfToken)(is_match(c)), .value = value->copy(value)};
                token.op = token.type < TokenSpace ? true : false;
                add_array_item(arr, token);
                value->clear(value);
            }
        }
        break;
        case StateEscape:
        {
            value->append(value, c);
            Token token = {.type = TokenText, .value = value->copy(value), false};
            add_array_item(arr, token);
            value->clear(value);
            state = get_lstate(line, i + 1);
        }
        break;
        }
    }
    value->free(value);
    return arr;
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/