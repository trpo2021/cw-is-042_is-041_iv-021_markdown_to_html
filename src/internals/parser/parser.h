#pragma once

#include <internals/parser/ast.h>
#include <internals/parser/token.h>

#define get_last_child(parrent) parrent->children[get_array_length(parrent->children) - 1]

Array(Token) tokenize(const String* line);

TNode* parse_document(const String* raw);