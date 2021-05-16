#pragma once

#include <internals/strings/strings.h>

/* array to represent every TokenType constant's name as string */
/* for debug may be */
static const char* const TOKEN_TO_STRING[] = {
    "TokenLineBreak",      "TokenUnderscore",    "TokenAsterisk",      "TokenGraveAccent",    "TokenEquals",
    "TokenMinus",          "TokenPlus",          "TokenOPAngleBraket", "TokenLattice",        "TokenExclamationMark",
    "TokenOPSquareBraket", "TokenCLAngleBraket", "TokenSpace",         "TokenCLSquareBraket", "TokenOPBraket",
    "TokenCLBraket",       "TokenNumber",        "TokenText"};

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
    string value;
    bool op;
} Token;

#define TokenToCharArray(token) token.value->Text(token.value)

#define TokenToString(token_type)                                                                                      \
    ((int)token_type < sizeof(TOKEN_TO_STRING) && (int)token_type >= 0) ? TOKEN_TO_STRING[token_type] : NULL
