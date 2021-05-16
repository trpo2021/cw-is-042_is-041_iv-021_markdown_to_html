#pragma once

#include <internals/parser/ast.h>
#include <internals/parser/token.h>

Array(Token) tokenize(const String* line);