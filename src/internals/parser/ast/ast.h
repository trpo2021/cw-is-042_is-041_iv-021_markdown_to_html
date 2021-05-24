#pragma once

#include <internals/collection/collection.h>
#include <internals/strings/strings.h>

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

TNode* get_tnode_last_child(TNode* parrent);

void free_tnode(TNode* root);

void add_tnode(TNode* parrent, TNode* child);

void remove_tnode(TNode* parrent, size_t index);

bool is_root_tnode(TNode* node);

bool is_leaf_tnode(TNode* node);

size_t get_tnode_lvl(TNode* node);
