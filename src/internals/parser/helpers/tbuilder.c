#include <internals/memext/memext.h>
#include <internals/parser/helpers/tbuilder.h>

typedef enum
{
    InitialStackCapacity = 10
} TBuilderConstants;

typedef struct _pstate_stack
{
    int64_t cp;
    int64_t cap;
    TNode** anchors;
} PStateStack;

/******************************
 *                            *
 *  Section: Stack functions  *
 *                            *
 ******************************/

static PStateStack* create_stack(size_t capacity)
{
    PStateStack* stack = mem_alloc(sizeof(PStateStack));
    stack->cap = capacity;
    stack->cp = -1;
    stack->anchors = mem_alloc(stack->cap * sizeof(TNode*));
    return stack;
}

static void add_anchor(TBuilder* builder, TNode** anchor)
{
    if (builder->states->cap - 1 <= builder->states->cp)
    {
        builder->states->cap = ((builder->states->cap + 1) * 2);
        builder->states->anchors = mem_realloc(builder->states->anchors, sizeof(TNode**) * builder->states->cap);
    }
    builder->states->anchors[++builder->states->cp] = *anchor;
}

static inline TNode* remove_anchor(TBuilder* builder)
{
    return builder->states->anchors[builder->states->cp--];
}

static inline TNode* get_anchor(TBuilder* builder)
{
    return builder->states->cp >= 0 ? builder->states->anchors[builder->states->cp] : NULL;
}

static void stack_free(PStateStack* stack)
{
    free(stack->anchors);
    free(stack);
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/

/******************************
 *                            *
 *  Section: Helper functions *
 *                            *
 ******************************/

static inline void nullify_header_underline(TNode* header)
{
    header->type = NodeSpan;
    sclear(header->head);
    sconcat(header->head, "<span>");
    header->nesting = false;
}

static inline void connect_to_anchor(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder);
    add_tnode(anchor, *node);
}

static inline void return_back(TBuilder* builder, TNode** node)
{
    remove_anchor(builder);
    builder->build_tree(builder, node);
}

static inline void write_content_to_node(TNode* node, String* content)
{
    sconcat(node->content, sraw(content));
}

static void close_section(TBuilder* builder, TNode** node)
{
    while (builder->states->cp > 0)
    {
        remove_anchor(builder);
    }

    TNode* anchor = get_anchor(builder);
    TNode* new_sec = init_tnode(NodeSection, screate("<section>"), NULL, true);
    add_tnode(anchor->parrent, *node);
    add_tnode(anchor->parrent, new_sec);

    remove_anchor(builder);
    add_anchor(builder, &new_sec);
}

static inline void wrap_to_paragraph(TNode** parrent, TNode** child)
{
    TNode* p = init_tnode(NodeParagraph, screate("<p>"), NULL, true);
    add_tnode(p, *child);
    remove_tnode(*parrent, get_array_length((*parrent)->children) - 1);
    add_tnode(*parrent, p);
}

static void process_hunderline_node(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder);
    TNode* last_child = get_tnode_last_child(anchor);
    if (last_child && last_child->type == NodeSpan)
    {
        add_tnode(*node, last_child);
        remove_tnode(anchor, get_array_length(anchor->children) - 1);
        add_tnode(anchor, *node);
        (*node)->type = NodeHeadingInline;
        return;
    }
    nullify_header_underline(*node);
    add_tnode(anchor, *node);
}

static void process_span_node(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder);
    TNode* last_child = get_tnode_last_child(anchor);
    if (last_child && last_child->type == NodeSpan)
    {
        wrap_to_paragraph(&anchor, &last_child);
        last_child = get_tnode_last_child(anchor);
        add_anchor(builder, &last_child);
        builder->build_tree(builder, node);
        return;
    }
    add_tnode(anchor, *node);
}

static void process_br_node(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder);
    TNode* last_child = get_tnode_last_child(anchor);
    if (last_child && last_child->type == NodeSpan)
    {
        wrap_to_paragraph(&anchor, &last_child);
    }
    free_tnode(*node);
}

static void switch_to_blockquote(TBuilder* builder, TNode** node)
{
    connect_to_anchor(builder, node);
    TNode* last_bq = *node;
    while (last_bq->children[0]->type == NodeBlockquote)
    {
        last_bq = last_bq->children[0];
    }
    TNode* after_bq = last_bq->children[0];
    wrap_to_paragraph(&last_bq, &after_bq);
    add_anchor(builder, &last_bq);
    after_bq = last_bq->children[0];
    add_anchor(builder, &after_bq);
}

static void switch_to_list(TBuilder* builder, TNode** node)
{
    add_anchor(builder, node);
    TNode* child = (*node)->children[0];
    if (child->type == NodeBlockquote)
    {
        remove_tnode(*node, 0);
        switch_to_blockquote(builder, &child);
        return;
    }
    wrap_to_paragraph(node, &child);
    child = (*node)->children[0];
    add_anchor(builder, &child);
}

static inline void add_li_lvl(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder)->parrent;
    add_tnode(anchor->children[get_array_length(anchor->children) - 1], *node);
}

static inline void combine_lists(TBuilder* builder, TNode** list)
{
    TNode* anchor = get_anchor(builder)->parrent;
    add_tnode(anchor, (*list)->children[0]);
    remove_anchor(builder);
    switch_to_list(builder, &(*list)->children[0]);
    (*list)->children[0] = NULL;
    free_tnode(*list);
}

static void add_node_to_list(TBuilder* builder, TNode** node)
{
    switch ((*node)->type)
    {
    case NodeBlockquote:
        switch_to_blockquote(builder, node);
        break;
    case NodeHeadingInline:
        add_li_lvl(builder, node);
        break;
    case NodePre:
        add_li_lvl(builder, node);
        add_anchor(builder, node);
        break;
    default:
        add_tnode(get_anchor(builder), init_tnode(NodeParagraph, screate("<p>"), NULL, true));
        add_anchor(builder, &(get_anchor(builder)->children[get_array_length(get_anchor(builder)->children) - 1]));
        builder->build_tree(builder, node);
        break;
    }
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/

/******************************
 *                            *
 *  Section: Tbuilder handle  *
 *                            *
 ******************************/

void handle_default(TBuilder* builder, TNode** node)
{
    switch ((*node)->type)
    {
    case NodeHorizontalLine:
        close_section(builder, node);
        break;
    case NodeHeadingUnderline:
        process_hunderline_node(builder, node);
        break;
    case NodePre:
        connect_to_anchor(builder, node);
        add_anchor(builder, node);
        break;
    case NodeSpan:
        process_span_node(builder, node);
        break;
    case NodeBlockquote:
        switch_to_blockquote(builder, node);
        break;
    case NodeBreakLine:
        process_br_node(builder, node);
        break;
    case NodeUOList:
    case NodeOList:
        (*node)->offset = 0;
        connect_to_anchor(builder, node);
        switch_to_list(builder, &(*node)->children[0]);
        break;
    default:
        connect_to_anchor(builder, node);
        break;
    }
}

void handle_codeblock(TBuilder* builder, TNode** node)
{
    // TODO: prefetch
    if ((*node)->type == NodePre)
    {
        remove_anchor(builder);
    }
    else
    {
        write_content_to_node(get_anchor(builder)->children[0]->children[0], builder->raw_text);
    }
    free_tnode(*node);
}

void handle_blockquote(TBuilder* builder, TNode** node)
{
    if ((*node)->type == NodeBlockquote)
    {
        uint8_t old_nesting = 1, new_nesting = 1;
        TNode* old_bq = get_anchor(builder);
        TNode* new_bq = *node;
        for (bool stop = false; !stop;)
        {
            if (old_bq->parrent->type != NodeBlockquote && new_bq->children[0]->type != NodeBlockquote)
            {
                break;
            }
            old_bq->parrent->type == NodeBlockquote ? (old_bq = old_bq->parrent, ++old_nesting) : 0;
            new_bq->children[0]->type == NodeBlockquote ? (new_bq = new_bq->children[0], ++new_nesting) : 0;
            (new_nesting > old_nesting) ? (stop = true) : 0;
        }
        if (old_nesting == new_nesting)
        {
            add_tnode(get_anchor(builder), init_tnode(NodeParagraph, screate("<p>"), NULL, true));
            TNode* p = get_tnode_last_child(get_anchor(builder));
            add_tnode(p, new_bq->children[0]);
            new_bq->children[0] = NULL;
            add_anchor(builder, &p);
        }
        else if (old_nesting < new_nesting)
        {
            new_bq->parrent->children[0] = NULL;
            switch_to_blockquote(builder, &new_bq);
        }
        else
        {
            return_back(builder, node);
            return;
        }
        free_tnode(*node);
        return;
    }
    return_back(builder, node);
}

void handle_paragraph(TBuilder* builder, TNode** node)
{
    switch ((*node)->type)
    {
    case NodeHeadingUnderline:
        nullify_header_underline(*node);
    case NodeSpan:
        connect_to_anchor(builder, node);
        break;
    case NodeBreakLine:
        free_tnode(*node);
        remove_anchor(builder);
        break;
    default:
        return_back(builder, node);
        break;
    }
}

void handle_list(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder)->parrent;
    if ((*node)->type == NodeOList || (*node)->type == NodeUOList)
    {
        if (anchor->offset < (*node)->offset)
        {
            add_li_lvl(builder, node);
            switch_to_list(builder, &(*node)->children[0]);
        }
        else if (anchor->offset == (*node)->offset && (*node)->type == anchor->type)
        {
            combine_lists(builder, node);
        }
        else
        {
            return_back(builder, node);
        }
        return;
    }
    else if ((*node)->type > NodeBreakLine && (*node)->offset > anchor->offset)
    {
        add_node_to_list(builder, node);
        return;
    }
    return_back(builder, node);
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/

/******************************
 *                            *
 *   Section: Tbuilder main   *
 *                            *
 ******************************/

typedef enum
{
    StateDefault,
    StateParagraph,
    StateCodeBlock,
    StateList,
    StateBlockquote
} TypeOfPState;

static const TypeOfPState STATE_TABLE[] = {
    [NodeSection] = StateDefault,     [NodePre] = StateCodeBlock,         [NodeListItem] = StateList,
    [NodeParagraph] = StateParagraph, [NodeBlockquote] = StateBlockquote,
};

static const void (*HANDLE_TABLE[])(TBuilder*, TNode**) = {
    [StateDefault] = handle_default, [StateCodeBlock] = handle_codeblock,   [StateParagraph] = handle_paragraph,
    [StateList] = handle_list,       [StateBlockquote] = handle_blockquote,
};

static void build_tree(TBuilder* builder, TNode** node)
{
    HANDLE_TABLE[STATE_TABLE[get_anchor(builder)->type]](builder, node);
}

void init_builder(TBuilder* builder, TNode** st_anchor)
{
    builder->states = create_stack(InitialStackCapacity);
    builder->build_tree = build_tree;
    add_anchor(builder, st_anchor);
}

void free_builder(TBuilder* builder)
{
    stack_free(builder->states);
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/