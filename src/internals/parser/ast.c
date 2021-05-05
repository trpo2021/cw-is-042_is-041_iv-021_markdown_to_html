#include <internals/parser/ast.h>

TNode* InitNode(TypeOfTNode type, string head, string content, bool nested)
{
    TNode* node = malloc(sizeof(TNode));
    node->type = type;
    node->head = head;
    node->content = content;
    node->nested = nested;
    node->parrent = NULL;
    node->children = NULL;
    return node;
}

void TreeFree(TNode* node)
{
    if (node)
    {
        if (node->head)
        {
            node->head->Free(node->head);
        }
        if (node->content)
        {
            node->content->Free(node->content);
        }
        if (node->children)
        {
            for (size_t i = 0; i < ArrayListGetLength(node->children); i++)
            {
                TreeFree(node->children[i]);
            }
            ArrayListFree(node->children);
        }
        free(node);
    }
}

void NodeAdd(TNode* parrent, TNode* child)
{
    child->parrent = parrent;
    ArrayListAdd(parrent->children, child);
}

bool IsRoot(TNode* node)
{
    return (node->parrent == NULL) ? true : false;
}

bool IsLeaf(TNode* node)
{
    return (ArrayListGetLength(node->children) == 0) ? true : false;
}

size_t GetNodeLevel(TNode* node)
{
    return (IsRoot(node)) ? 0 : GetNodeLevel(node->parrent) + 1;
}
