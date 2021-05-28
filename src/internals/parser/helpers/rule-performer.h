#pragma once

#include <internals/parser/ast/ast.h>
#include <internals/parser/grammar/grammar.h>

typedef enum
{
    ModeAvaliableAll = RuleHorizontalLine,
    ModeAvaliableFromList = RuleOList,
    ModeAvaliableFromBlockquote = RuleBlockquote,
    ModeAvaliableFromHeader = RuleHeadingInline,
    ModeAvaliableOnlyText = RuleEmphasis
} RPMode;

typedef struct rule_performer
{
    struct
    {
        RPMode mode;
        size_t cp;
    };
    size_t count;
    Array(Token) tokens;
    TNode* (*invoke)(struct rule_performer* perf, size_t lim);
} RulePerformer;

void init_performer(RulePerformer* perf, Array(Token) tokens, size_t pos);

/******************************
 *                            *
 *  Section: Helper functions *
 *                            *
 ******************************/

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

static inline bool is_token_in_term(Term term, TypeOfToken token)
{
    int32_t left = 0, right = term.count - 1;
    while (left <= right)
    {
        int32_t mid = (int32_t)(((uint32_t)left + (uint32_t)right) >> 1);
        if (term.tokens[mid] == token)
        {
            return true;
        }
        term.tokens[mid] < token ? (left = mid + 1) : (right = mid - 1);
    }
    return false;
}

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