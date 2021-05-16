#pragma once

#include <internals/parser/collection.h>
#include <internals/strings/strings.h>
#include <stdio.h>

typedef enum
{
    NodeBody,
    NodeSection,

    NodeHorizontalLine,
    NodeBreakLine,

    NodePre,

    NodeOList,
    NodeUOList,

    NodeHeadingInline,
    NodeHeadingUnderline,
    NodeBlockquote,

    NodeInlineCode,
    NodeEmphasis,
    NodeImage,
    NodeLink,

    NodeListItem,
    NodeCode,
    NodeAlt,
    NodeSrc,

    NodeParagraph,

    NodeSpan,
} TypeOfTNode;

typedef struct _tnode
{
    struct
    {
        TypeOfTNode type;
        String* head;
        /* may be NULL */
        String* content;
        bool nesting;
        size_t offset;
    };
    struct _tnode* parrent;
    Array(struct _tnode*) children;
} TNode;

TNode* init_tnode(TypeOfTNode type, String* head, String* content, bool nesting);

void free_tnode(TNode* root);

void print_tnode(TNode* node, FILE* out);

void add_tnode(TNode* parrent, TNode* child);

bool is_root_tnode(TNode* node);

bool is_leaf_tnode(TNode* node);

size_t get_tnode_lvl(TNode* node);
