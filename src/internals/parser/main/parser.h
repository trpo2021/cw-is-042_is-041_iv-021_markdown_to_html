#pragma once

#include <internals/parser/helpers/rule-performer.h>
#include <internals/parser/helpers/tbuilder.h>

#define get_last_child(parrent) parrent->children[get_array_length(parrent->children) - 1]

/* convert string to tokens */
/* @param line line of raw document */
/* @return array of tokens */
Array(Token) tokenize(const String* line);

/* main parser function */
/* @param raw text from document */
/* @return AST root */
TNode* parse_document(const String* raw);