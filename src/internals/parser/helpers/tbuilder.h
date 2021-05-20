#pragma once

#include <internals/parser/main/parser.h>

typedef struct
{
    size_t cp;
    size_t cap;
    TNode** anchors;
} PStateStack;

typedef struct _tbuilder
{
    PStateStack* states;
    String* raw;
    void (*build_tree)(struct _tbuilder* builder, TNode** node_ptr);
} TBuilder;

/* initialize tree builder with start anchor */
/* @param builder self structure */
/* @param st_anchor start anchor */
void init_builder(TBuilder* builder, TNode** st_anchor);

/* free tree builder */
/* @param builder self structure */
void free_builder(TBuilder* builder);