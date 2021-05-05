#include <internals/parser/ast.h>

void TreePrint(TNode* node, FILE* out)
{
    if (node)
    {
        fprintf(out, "%zu  | ", GetNodeLevel(node));
        for (size_t i = 0; i < GetNodeLevel(node); i++)
        {
            fprintf(out, "%s", " ");
        }
        if (node->head)
        {
            fprintf(out, "%s", node->head->Text(node->head));
        }
        if (node->content)
        {
            fprintf(out, "%s", node->content->Text(node->content));
        }
        fprintf(out, "%s", "\n");
        for (size_t i = 0; i < collection_get_size(node->children); i++)
        {
            TreePrint(node->children[i], out);
        }
    }
}