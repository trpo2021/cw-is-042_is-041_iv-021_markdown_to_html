#pragma once

#include <internals/parser/collection.h>
#include <internals/parser/token.h>

/* may be should be static in .c */

collection(Token_t) tokenize(const string raw);