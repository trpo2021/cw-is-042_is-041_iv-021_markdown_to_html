#pragma once

#include <internals/strings/strings.h>

/* array to represent every TokenType constant's name as string */
static const char* const EnumToString[] = {"TypeUnderscore",
                                           "TypeLineBreak",
                                           "TypeAsterisk",
                                           "TypePlus",
                                           "TypeMinus",
                                           "TypeLattice",
                                           "TypeTab",
                                           "TypeSpace",
                                           "TypeEscape",
                                           "TypeGraveAccent",
                                           "TypeExclamationMark",
                                           "TypeEquals",
                                           "TypeOPSquareBraket",
                                           "TypeCLSquareBraket",
                                           "TypeOPBraket",
                                           "TypeCLBraket",
                                           "TypeOPAngleBraket",
                                           "TypeCLAngleBraket",
                                           "TypeText"};

typedef enum
{
    /* _ */
    TypeUnderscore,
    /* \n */
    TypeLineBreak,
    /* ** */
    TypeAsterisk,
    /* + */
    TypePlus,
    /* - */
    TypeMinus,
    /* - */
    TypeLattice,
    /* \\t */
    TypeTab,
    /*  */
    TypeSpace,
    /* \ */
    TypeEscape,
    /* ` */
    TypeGraveAccent,
    /* ! */
    TypeExclamationMark,
    /* = */
    TypeEquals,

    /* Brakets */

    /* [ */
    TypeOPSquareBraket,
    /* ] */
    TypeCLSquareBraket,
    /* ( */
    TypeOPBraket,
    /* ) */
    TypeCLBraket,
    /* < */
    TypeOPAngleBraket,
    /* > */
    TypeCLAngleBraket,

    /* Other */

    /* Some text */
    TypeText

} TokenType;

typedef struct
{
    TokenType type;
    string value;
} Token_t;

#define GET_TOKEN_NAME(token_type)                                                                                     \
    ((int)token_type < sizeof(EnumToString) && (int)token_type >= 0) ? EnumToString[token_type] : NULL
// # - + * ( ) [ ] \ !