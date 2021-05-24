#pragma once

#include <internals/parser/ast/ast.h>

/* main parser function */
/* @param raw text from document */
/* @return AST root */
TNode* parse_document(const String* raw);