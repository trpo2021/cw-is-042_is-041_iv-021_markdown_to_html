#include <ctest.h>
#include <internals/parser/main/parser.h>

static TNode* setup_builder_for_test(TBuilder* builder)
{
    TNode* body = init_tnode(NodeBody, NULL, NULL, true);
    TNode* section = init_tnode(NodeSection, NULL, NULL, true);
    add_tnode(body, section);
    init_builder(builder, &section);
    return body;
}

CTEST(tbuilder, close_section)
{
    TBuilder builder = {0};
    TNode* root = setup_builder_for_test(&builder);
    TNode* hr = init_tnode(NodeHorizontalLine, NULL, NULL, false);

    builder.build_tree(&builder, &hr);

    ASSERT_EQUAL(0, builder.states->cp);
    ASSERT_EQUAL(3, get_array_length(root->children));
    ASSERT_EQUAL(NodeSection, root->children[0]->type);
    ASSERT_EQUAL(NodeHorizontalLine, root->children[1]->type);
    ASSERT_EQUAL(NodeSection, root->children[2]->type);
    for (size_t i = 0; i < get_array_length(root->children); ++i)
    {
        ASSERT_NULL(root->children[i]->children);
    }

    free_builder(&builder);
    free_tnode(root);
}