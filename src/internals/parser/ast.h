#pragma once

#include <internals/parser/collection.h>
#include <internals/strings/strings.h>
#include <stdio.h>

typedef enum
{
    NodeBody,
    NodeSection,
    NodeHeading,
    NodeBlockquote,
    NodeOList,
    NodeUOList,
    NodeInlineCode,
    NodeEmphasis,
    NodeBlockCode,
    NodeBreakLine,
    NodeHorizontalLine,
    NodeImage,
    NodeLink,
    NodeParagraph,
    NodeSpan,
} TypeOfTNode;

typedef struct _tnode
{
    struct
    {
        TypeOfTNode type;
        string head;
        string content;
        // tmp
        bool nested;
    };
    struct _tnode* parrent;
    ArrayList(struct _tnode*) children;
} TNode;

TNode* InitNode(TypeOfTNode type, string head, string content, bool nested);

void TreeFree(TNode* root);

void TreePrint(TNode* node, FILE* out);

void NodeAdd(TNode* parrent, TNode* child);

bool IsRoot(TNode* node);

bool IsLeaf(TNode* node);

size_t GetNodeLevel(TNode* node);
