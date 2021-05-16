#pragma once

#include <internals/parser/ast.h>
#include <internals/parser/token.h>

ArrayList(Token) Tokenize(const string line);