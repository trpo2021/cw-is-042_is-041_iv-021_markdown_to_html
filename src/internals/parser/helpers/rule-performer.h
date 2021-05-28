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
    Token* tokens;
    TNode* (*invoke)(struct rule_performer* perf, size_t lim);
} RulePerformer;

void init_performer(RulePerformer* perf, Token* tokens, size_t pos);

size_t skip_spaces(size_t index, Token* tokens);