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
        string head;
        /* may be NULL */
        string content;
        bool nesting;
        size_t offset;
    };
    struct _tnode* parrent;
    ArrayList(struct _tnode*) children;
} TNode;

TNode* InitNode(TypeOfTNode type, string head, string content, bool nesting);

void TreeFree(TNode* root);

void TreePrint(TNode* node, FILE* out);

void NodeAdd(TNode* parrent, TNode* child);

bool IsRoot(TNode* node);

bool IsLeaf(TNode* node);

size_t GetNodeLevel(TNode* node);
