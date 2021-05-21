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

CTEST(tbuilder, spans_to_paragraph)
{
    TBuilder builder = {0};
    TNode* root = setup_builder_for_test(&builder);
    TNode* span = init_tnode(NodeSpan, NULL, NULL, false);

    builder.build_tree(&builder, &span);

    ASSERT_EQUAL(1, get_array_length(root->children[0]->children));
    ASSERT_NOT_EQUAL(NodeParagraph, get_last_child(root->children[0])->type);

    for (size_t i = 0; i < 10; ++i)
    {
        TNode* tmp = init_tnode(NodeSpan, NULL, NULL, false);
        builder.build_tree(&builder, &tmp);
    }

    ASSERT_EQUAL(NodeParagraph, get_last_child(root->children[0])->type);
    ASSERT_EQUAL(11, get_array_length(get_last_child(root->children[0])->children));

    free_builder(&builder);
    free_tnode(root);
}

CTEST(tbuilder, header_underline_single)
{
    TBuilder builder = {0};
    TNode* root = setup_builder_for_test(&builder);
    TNode* hu = init_tnode(NodeHeadingUnderline, NULL, create_string("==="), true);

    builder.build_tree(&builder, &hu);

    ASSERT_EQUAL(NodeSpan, get_last_child(root->children[0])->type);
    ASSERT_STR("===", get_last_child(root->children[0])->content->text(get_last_child(root->children[0])->content));

    free_builder(&builder);
    free_tnode(root);
}