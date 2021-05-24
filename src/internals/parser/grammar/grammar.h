#pragma once

#include <internals/parser/grammar/token.h>

typedef enum
{
    MaxTokensInTerm = 5,
} GrammarConstants;

typedef enum
{
    RuleHorizontalLine,
    RuleLineBreak,
    RuleH1Underline,
    RuleH2Underline,
    RuleCodeBlock,
    RuleOList,
    RuleUOList,
    RuleBlockquote,
    RuleHeadingInline,
    RuleEmphasis,
    RuleCodeInline,
    RuleImage,
    RuleLink,
    RuleAutoLink,
    RuleUnknown
} TypeOfRule;

typedef enum
{
    HorizontalLineLowerLimit = 3,
    HeaderUnderlineLowerLimit = 2,
    CodeBlockLowerLimit = 3,
    BlockquoteUpperLimit = 15,
    HeaderInlineLowerLimit = 1,
    HeaderInlineUpperLimit = 6,
    WhitespaceForBreakLineLowerLimit = 2,

} RuleLimits;

typedef struct
{
    TypeOfToken tokens[MaxTokensInTerm];
    uint8_t count;
} Term;

static const Term HR_TERM = {{TokenUnderscore, TokenAsterisk}, 2};
static const Term BR_TERM = {{TokenLineBreak}, 1};
static const Term H1U_TERM = {{TokenEquals}, 1};
static const Term H2U_TERM = {{TokenMinus}, 1};
static const Term CODE_TERM = {{TokenGraveAccent}, 1};

static const Term OLIST_TERM = {{TokenNumber}, 1};
static const Term UOLIST_TERM = {{TokenAsterisk, TokenMinus, TokenPlus}, 3};

static const Term BLOCKQUOTE_TERM = {{TokenCLAngleBracket}, 1};
static const Term HI_TERM = {{TokenLattice}, 1};

static const Term LINK_END_FIRST_TERM = {{TokenCLSquareBracket}, 1};
static const Term LINK_END_LAST_TERM = {{TokenCLBracket}, 1};

static const Term ALINK_END_TERM = {{TokenCLAngleBracket}, 1};
static const Term LINK_TERM = {{TokenOPSquareBracket}, 1};
static const Term IMG_TERM = {{TokenExclamationMark}, 1};

static const Term EMPHASIS_TERM = {{TokenUnderscore, TokenAsterisk}, 2};

static const Term WHITESPACE_TERM = {{TokenSpace}, 1};