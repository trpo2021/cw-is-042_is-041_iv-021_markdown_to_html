#pragma once

#include <internals/parser/helpers/rule-performer.h>
#include <internals/parser/helpers/tbuilder.h>

#define get_last_child(parrent) parrent->children[get_array_length(parrent->children) - 1]

Array(Token) tokenize(const String* line);

/* main parser function */
/* @param raw text from document */
/* @return AST root */
TNode* parse_document(const String* raw);