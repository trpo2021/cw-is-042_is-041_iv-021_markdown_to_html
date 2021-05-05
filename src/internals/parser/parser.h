#pragma once

#include <internals/parser/collection.h>
#include <internals/parser/token.h>

collection(Token_t) Tokenize(const string raw);