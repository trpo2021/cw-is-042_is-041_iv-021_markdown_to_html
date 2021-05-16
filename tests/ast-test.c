#include <ctest.h>
#include <internals/parser/ast.h>
#include <stdio.h>

CTEST(ast, node_operations)
{
    TNode* root = InitNode(NodeBody, create("<body>"), NULL, false);
    ASSERT_TRUE(IsRoot(root));
    ASSERT_TRUE(IsLeaf(root));
    ASSERT_EQUAL(0, GetNodeLevel(root));
    TNode* node = InitNode(NodeHeadingInline, create("<h1>"), create("Header content"), false);
    NodeAdd(root, node);
    for (size_t i = 0; i < ArrayListGetLength(root->children); i++)
    {
        ASSERT_STR("<h1>", root->children[i]->head->Text(root->children[i]->head));
        ASSERT_STR("Header content", root->children[i]->content->Text(root->children[i]->content));
    }
    ASSERT_FALSE(IsRoot(root->children[0]));
    ASSERT_FALSE(IsLeaf(root));
    ASSERT_TRUE(IsLeaf(root->children[0]));
    ASSERT_EQUAL(1, GetNodeLevel(root->children[0]));
    TreeFree(root);
}

CTEST(ast, tree_build)
{
    TNode* root = InitNode(NodeBody, create("<body>"), NULL, false);
    for (size_t i = 0; i < 10; i++)
    {
        NodeAdd(root, InitNode(NodeHeadingInline, create("<h1>"), create("test"), false));
    }
    for (size_t i = 0; i < ArrayListGetLength(root->children); i++)
    {
        ASSERT_STR("<h1>", root->children[i]->head->Text(root->children[i]->head));
        ASSERT_STR("test", root->children[i]->content->Text(root->children[i]->content));
    }
    TreeFree(root);
}

CTEST(ast, tree_print)
{
    TNode* root = InitNode(NodeBody, create("<body>"), NULL, false);
    NodeAdd(root, InitNode(NodeSection, create("<section>"), NULL, false));
    for (size_t i = 2, j = 0; i < 6; i++)
    {
        if (i % 4 == 0)
        {
            NodeAdd(root, InitNode(NodeSection, create("<section>"), NULL, false));
            j++;
        }
        if (i % 2 == 0)
        {
            NodeAdd(root->children[j], InitNode(NodeHeadingInline, create("<h1>"), NULL, false));
            NodeAdd(root->children[j]->children[0], InitNode(NodeHeadingInline, create("<span>"), create(""), false));
        }
        else
        {
            NodeAdd(root->children[j], InitNode(NodeHeadingInline, create("<span>"), create(""), false));
        }
    }
    FILE* out = fopen("tree.txt", "w");
    TreePrint(root, out);
    TreeFree(root);
    fclose(out);
    remove("tree.txt");
}