#pragma once

#include <internals/strings/strings.h>

typedef enum
{
    TokenLineBreak,
    TokenUnderscore,
    TokenAsterisk,
    TokenGraveAccent,
    TokenEquals,
    TokenMinus,
    TokenPlus,
    TokenOPAngleBracket,
    TokenLattice,
    TokenExclamationMark,
    TokenOPSquareBracket,
    TokenCLAngleBracket,
    TokenSpace,
    TokenCLSquareBracket,
    TokenOPBracket,
    TokenCLBracket,
    TokenNumber,
    TokenText
} TypeOfToken;

typedef struct
{
    TypeOfToken type;
    String* value;
    bool op;
} Token;