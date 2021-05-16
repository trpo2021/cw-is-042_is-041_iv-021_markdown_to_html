#include <ctest.h>
#include <internals/parser/ast.h>
#include <stdio.h>

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

CTEST(ast, tree_print)
{
    TNode* root = init_tnode(NodeBody, create_string("<body>"), NULL, false);
    add_tnode(root, init_tnode(NodeSection, create_string("<section>"), NULL, false));
    for (size_t i = 2, j = 0; i < 6; i++)
    {
        if (i % 4 == 0)
        {
            add_tnode(root, init_tnode(NodeSection, create_string("<section>"), NULL, false));
            j++;
        }
        if (i % 2 == 0)
        {
            add_tnode(root->children[j], init_tnode(NodeHeadingInline, create_string("<h1>"), NULL, false));
            add_tnode(root->children[j]->children[0],
                      init_tnode(NodeHeadingInline, create_string("<span>"), create_string(""), false));
        }
        else
        {
            add_tnode(root->children[j],
                      init_tnode(NodeHeadingInline, create_string("<span>"), create_string(""), false));
        }
    }
    FILE* out = fopen("tree.txt", "w");
    print_tnode(root, out);
    free_tnode(root);
    fclose(out);
    remove("tree.txt");
}