#pragma once

#include <internals/collection/collection.h>
#include <internals/parser/grammar/token.h>

/* convert string to tokens */
/* @param line line of raw document */
/* @return array of tokens */
Array(Token) tokenize(const String* line);