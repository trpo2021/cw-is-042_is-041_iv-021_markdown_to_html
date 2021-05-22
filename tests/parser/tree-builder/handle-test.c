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

CTEST(tbuilder, header_underline_correct)
{
    TBuilder builder = {0};
    TNode* root = setup_builder_for_test(&builder);
    TNode* span = init_tnode(NodeSpan, NULL, NULL, false);
    TNode* hu = init_tnode(NodeHeadingUnderline, NULL, create_string("==="), true);

    builder.build_tree(&builder, &span);

    ASSERT_EQUAL(NodeSpan, get_last_child(root->children[0])->type);

    builder.build_tree(&builder, &hu);

    ASSERT_EQUAL(NodeHeadingUnderline, get_last_child(root->children[0])->type);
    ASSERT_EQUAL(1, get_array_length(hu->children));

    free_builder(&builder);
    free_tnode(root);
}

CTEST(tbuilder, header_underline_with_paragraph)
{
    TBuilder builder = {0};
    TNode* root = setup_builder_for_test(&builder);

    for (size_t i = 0; i < 2; ++i)
    {
        TNode* tmp = init_tnode(NodeSpan, NULL, NULL, false);
        builder.build_tree(&builder, &tmp);
    }

    ASSERT_EQUAL(NodeParagraph, get_last_child(root->children[0])->type);
    ASSERT_EQUAL(2, get_array_length(get_last_child(root->children[0])->children));

    for (size_t i = 0; i < get_array_length(get_last_child(root->children[0])->children); ++i)
    {
        ASSERT_EQUAL(NodeSpan, get_last_child(root->children[0])->children[i]->type);
    }

    free_builder(&builder);
    free_tnode(root);
}

CTEST(tbuilder, header_inline_to_paragraph_in_blockquote)
{
    TBuilder builder = {0};
    TNode* root = setup_builder_for_test(&builder);
    TNode* bq = init_tnode(NodeBlockquote, NULL, NULL, true);
    add_tnode(bq, init_tnode(NodeHeadingInline, NULL, NULL, true));

    builder.build_tree(&builder, &bq);

    ASSERT_EQUAL(NodeParagraph, bq->children[0]->type);

    free_builder(&builder);
    free_tnode(root);
}

CTEST(tbuilder, span_to_paragraph_in_blockquote)
{
    TBuilder builder = {0};
    TNode* root = setup_builder_for_test(&builder);
    TNode* bq = init_tnode(NodeBlockquote, NULL, NULL, true);
    add_tnode(bq, init_tnode(NodeSpan, NULL, NULL, false));

    builder.build_tree(&builder, &bq);

    ASSERT_EQUAL(NodeParagraph, bq->children[0]->type);

    free_builder(&builder);
    free_tnode(root);
}

CTEST(tbuilder, switch_list_to_blockquote)
{
    TBuilder builder = {0};
    TNode* root = setup_builder_for_test(&builder);
    TNode* ul = init_tnode(NodeUOList, NULL, NULL, true);
    TNode* li = init_tnode(NodeListItem, NULL, NULL, true);
    add_tnode(ul, li);
    TNode* bq = init_tnode(NodeBlockquote, NULL, NULL, true);
    add_tnode(bq, init_tnode(NodeSpan, NULL, NULL, false));
    add_tnode(li, bq);

    builder.build_tree(&builder, &ul);

    ASSERT_EQUAL(NodeParagraph, builder.states->anchors[builder.states->cp]->type);
    ASSERT_EQUAL(NodeBlockquote, builder.states->anchors[builder.states->cp - 1]->type);
    ASSERT_EQUAL(NodeListItem, builder.states->anchors[builder.states->cp - 2]->type);

    free_builder(&builder);
    free_tnode(root);
}

CTEST(tbuilder, wrap_list_span_to_paragraph)
{
    TBuilder builder = {0};
    TNode* root = setup_builder_for_test(&builder);
    TNode* ul = init_tnode(NodeUOList, NULL, NULL, true);
    TNode* li = init_tnode(NodeListItem, NULL, NULL, true);
    add_tnode(li, init_tnode(NodeSpan, NULL, NULL, false));
    add_tnode(ul, li);

    builder.build_tree(&builder, &ul);

    ASSERT_EQUAL(NodeParagraph, builder.states->anchors[builder.states->cp]->type);

    free_builder(&builder);
    free_tnode(root);
}

CTEST(tbuilder, concat_lists_with_same_ctx)
{
    const char* items[] = {"item 1", "item 2", "item 3"};
    String* s = create_string("* item 1\n"
                              "+ item 2\n"
                              "- item 3\n");

    TNode* root = parse_document(s);
    TNode* ul = root->children[0]->children[0];

    ASSERT_EQUAL(3, get_array_length(ul->children));
    for (size_t i = 0; i < get_array_length(ul->children); ++i)
    {
        TNode* li = ul->children[i];
        ASSERT_EQUAL(NodeParagraph, li->children[1]->type);
        TNode* p = li->children[1];
        ASSERT_EQUAL(NodeSpan, p->children[0]->type);
        ASSERT_STR(items[i], p->children[0]->content->text(p->children[0]->content));
    }

    free_tnode(root);
    s->free(s);
}

CTEST(tbuilder, check_codeblock)
{
    TypeOfTNode types[] = {NodeBody, NodeSection, NodePre, NodeCode, NodeSpan};
    const char* code_content = "1. >> ## *test* [test](test)\n";
    const char* after_content = " header lvl 3";
    String* s = create_string("```\n");
    s->concat(s, code_content);
    s->concat(s, "```\n");
    s->concat(s, "###");
    s->concat(s, after_content);

    TNode* root = parse_document(s);
    TNode* tmp = root;
    for (size_t i = 0; tmp->children && i < sizeof(types) / sizeof(types[0]); ++i)
    {
        ASSERT_EQUAL(types[i], tmp->type);
        tmp = tmp->children[0];
    }
    ASSERT_STR(code_content, tmp->content->text(tmp->content));

    TNode* h3 = root->children[0]->children[1];
    ASSERT_EQUAL(NodeHeadingInline, h3->type);
    ASSERT_EQUAL(NodeSpan, h3->children[0]->type);
    ASSERT_STR(after_content, h3->children[0]->content->text(h3->children[0]->content));

    free_tnode(root);
    s->free(s);
}