#pragma once

#include <internals/strings/strings.h>

/* array to represent every TokenType constant's name as string */
static const char* const TOKEN_TO_STRING[] = {"TokenUnderscore",
                                              "TokenLineBreak",
                                              "TokenAsterisk",
                                              "TokenPlus",
                                              "TokenMinus",
                                              "TokenLattice",
                                              "TokenTab",
                                              "TokenSpace",
                                              "TokenEscape",
                                              "TokenGraveAccent",
                                              "TokenExclamationMark",
                                              "TokenEquals",
                                              "TokenOPSquareBraket",
                                              "TokenCLSquareBraket",
                                              "TokenOPBraket",
                                              "TokenCLBraket",
                                              "TokenOPAngleBraket",
                                              "TokenCLAngleBraket",
                                              "TokenText"};

typedef enum
{
    /* _ */
    TokenUnderscore,
    /* \n */
    TokenLineBreak,
    /* ** */
    TokenAsterisk,
    /* + */
    TokenPlus,
    /* - */
    TokenMinus,
    /* - */
    TokenLattice,
    /* \\t */
    TokenTab,
    /*  */
    TokenSpace,
    /* \ */
    TokenEscape,
    /* ` */
    TokenGraveAccent,
    /* ! */
    TokenExclamationMark,
    /* = */
    TokenEquals,

    /* Brakets */

    /* [ */
    TokenOPSquareBraket,
    /* ] */
    TokenCLSquareBraket,
    /* ( */
    TokenOPBraket,
    /* ) */
    TokenCLBraket,
    /* < */
    TokenOPAngleBraket,
    /* > */
    TokenCLAngleBraket,

    /* Other */

    /* Some text */
    TokenText

} TypeOfToken;

typedef struct
{
    TypeOfToken type;
    string value;
} Token;

#define TokenToString(token_type)                                                                                      \
    ((int)token_type < sizeof(TOKEN_TO_STRING) && (int)token_type >= 0) ? TOKEN_TO_STRING[token_type] : NULL
