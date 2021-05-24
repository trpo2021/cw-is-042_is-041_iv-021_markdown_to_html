#include <ctest.h>
#include <internals/parser/ast/ast.h>

CTEST(ast, node_operations)
{
    TNode* root = init_tnode(NodeBody, create_string("<body>"), NULL, false);
    ASSERT_TRUE(is_root_tnode(root));
    ASSERT_TRUE(is_leaf_tnode(root));
    ASSERT_EQUAL(0, get_tnode_lvl(root));
    TNode* node = init_tnode(NodeHeadingInline, create_string("<h1>"), create_string("Header content"), false);
    add_tnode(root, node);
    for (size_t i = 0; i < get_array_length(root->children); i++)
    {
        ASSERT_STR("<h1>", root->children[i]->head->text(root->children[i]->head));
        ASSERT_STR("Header content", root->children[i]->content->text(root->children[i]->content));
    }
    ASSERT_FALSE(is_root_tnode(root->children[0]));
    ASSERT_FALSE(is_leaf_tnode(root));
    ASSERT_TRUE(is_leaf_tnode(root->children[0]));
    ASSERT_EQUAL(1, get_tnode_lvl(root->children[0]));
    free_tnode(root);
}

CTEST(ast, tree_build)
{
    TNode* root = init_tnode(NodeBody, create_string("<body>"), NULL, false);
    for (size_t i = 0; i < 10; i++)
    {
        add_tnode(root, init_tnode(NodeHeadingInline, create_string("<h1>"), create_string("test"), false));
    }
    for (size_t i = 0; i < get_array_length(root->children); i++)
    {
        ASSERT_STR("<h1>", root->children[i]->head->text(root->children[i]->head));
        ASSERT_STR("test", root->children[i]->content->text(root->children[i]->content));
    }
    free_tnode(root);
}

CTEST(ast, remove_node)
{
    TNode* root = init_tnode(NodeBody, create_string("<body>"), NULL, false);
    remove_tnode(root, 0);
    add_tnode(root, init_tnode(NodeSection, NULL, NULL, true));
    free_tnode(root->children[0]);
    remove_tnode(root, 0);
    ASSERT_EQUAL(0, get_array_length(root->children));
    add_tnode(root, init_tnode(NodeParagraph, NULL, NULL, true));
    ASSERT_EQUAL(NodeParagraph, root->children[0]->type);
    free_tnode(root);
}

CTEST(ast, get_last_node_child)
{
    TNode* root = init_tnode(NodeBody, create_string("<body>"), NULL, false);
    ASSERT_NULL(get_tnode_last_child(root));
    add_tnode(root, init_tnode(NodeSection, NULL, NULL, true));
    ASSERT_EQUAL(NodeSection, get_tnode_last_child(root)->type);
    for (size_t i = 2; i < 8; ++i)
    {
        add_tnode(root, init_tnode((TypeOfTNode)i, NULL, NULL, true));
    }
    ASSERT_EQUAL(NodeHeadingInline, get_tnode_last_child(root)->type);
    free_tnode(root);
}