#pragma once

#include <internals/parser/ast/ast.h>

struct _pstate_stack;

typedef struct _tbuilder
{
    struct _pstate_stack* states;
    String* raw_text;
    void (*build_tree)(struct _tbuilder* builder, TNode** node_ptr);
} TBuilder;

void init_builder(TBuilder* builder, TNode** st_anchor);

void free_builder(TBuilder* builder);