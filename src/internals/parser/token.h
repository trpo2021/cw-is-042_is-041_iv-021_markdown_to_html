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
    String* value;
    bool op;
} Token;

#define get_token_value(token) token.value->text(token.value)

#define token_name_to_string(token_type)                                                                               \
    ((int)token_type < sizeof(TOKEN_TO_STRING) && (int)token_type >= 0) ? TOKEN_TO_STRING[token_type] : NULL
