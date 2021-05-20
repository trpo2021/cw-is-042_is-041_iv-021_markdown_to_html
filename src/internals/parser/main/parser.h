#pragma once

#include <internals/parser/helpers/rule-performer.h>

#define get_last_child(parrent) parrent->children[get_array_length(parrent->children) - 1]

Array(Token) tokenize(const String* line);

TNode* parse_document(const String* raw);