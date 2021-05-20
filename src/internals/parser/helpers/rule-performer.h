#pragma once

#include <internals/parser/ast/ast.h>
#include <internals/parser/grammar/grammar.h>

typedef enum
{
    /* in start of line */
    ModeAAL = 0,
    /* after li */
    ModeAFL = 5,
    /* after blockquote */
    ModeAFB = 7,
    /* after inline header */
    ModeAFH = 8,
    /* default */
    ModeAFE = 9
} RPMode;

typedef struct rule_performer
{
    struct
    {
        /* state in line */
        RPMode mode;
        /* current pos in tokens */
        size_t cp;
    };
    /* count of tokens in sequense */
    size_t count;
    /* token sequense */
    Array(Token) tokens;
    /* select rule and return tree node */
    TNode* (*invoke)(struct rule_performer* perf, size_t lim);
} RulePerformer;

void init_performer(RulePerformer* perf, Array(Token) tokens, size_t pos);

/******************************
 *                            *
 *  Section: Helper functions *
 *                            *
 ******************************/

/* @param index current position in token sequense */
/* @param tokens token sequense */
/* @return index of first non whitespace token in the sequense */
static inline size_t skip_spaces(size_t index, Array(Token) tokens)
{
    for (; index < get_array_length(tokens); ++index)
    {
        if (tokens[index].type != TokenSpace)
        {
            return index;
        }
    }
    return index;
}

/* @param term set of tokens for search */
/* @param token current token for check */
/* @return true if term contains token or false if it doesn't*/
static inline bool is_token_in_term(Term term, TypeOfToken token)
{
    int32_t left = 0, right = term.count - 1;
    while (left <= right)
    {
        int mid = (int32_t)(((uint32_t)left + (uint32_t)right) >> 1);
        if (term.tokens[mid] == token)
        {
            return true;
        }
        term.tokens[mid] < token ? (left = mid + 1) : (right = mid - 1);
    }
    return false;
}

/* @param term set of tokens for search */
/* @param lim limit for search */
/* @param count count of tokens for search */
/* @return last element's index in the token sequence or 0 if sequense doesn't contains */
static inline size_t find_end_pos(RulePerformer* perf, size_t lim, Term term, size_t count)
{
    for (size_t i = perf->cp, c_count = 0; i < lim; ++i)
    {
        is_token_in_term(term, perf->tokens[i].type) ? (++c_count) : (c_count = 0);
        if (c_count == count)
        {
            return i;
        }
    }
    return 0;
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/