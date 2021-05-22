#include <assert.h>
#include <internals/parser/helpers/tbuilder.h>

/* TODO: some refactorng */

#define STACK_INITIAL_CAP 10

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

/* initialize PStateStack */
/* @param capacity initial capacity */
/* @return pointer to created PStateStack */
static PStateStack* create_stack(size_t capacity)
{
    PStateStack* stack = malloc(sizeof(PStateStack));
    stack->cap = capacity;
    stack->cp = -1;
    stack->anchors = malloc(stack->cap * sizeof(TNode*));
    return stack;
}

/* add anchor to builder */
/* @param builder tree builder */
/* @param anchor node to push on stack */
static void add_anchor(TBuilder* builder, TNode** anchor)
{
    if (builder->states->cap - 1 <= builder->states->cp)
    {
        builder->states->cap = ((builder->states->cap + 1) * 2);
        TNode** tmp = realloc(builder->states->anchors, sizeof(TNode**) * builder->states->cap);
        assert(tmp);
        builder->states->anchors = tmp;
    }
    builder->states->anchors[++builder->states->cp] = *anchor;
}

/* remove anchor from builder */
/* @param builder tree builder */
/* @return pointer to removed anchor */
static TNode* remove_anchor(TBuilder* builder)
{
    return builder->states->anchors[builder->states->cp--];
}

/* peek anchor from builder */
/* @param builder tree builder */
/* @return pointer to peeked anchor or NULL if stack is empty */
static TNode* get_anchor(TBuilder* builder)
{
    return builder->states->cp >= 0 ? builder->states->anchors[builder->states->cp] : NULL;
}

/* free PStateStack */
/* @param stack pointer to be free */
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

/* in case, when we can't wrap span in header */
/* @param header node to convert to span node */
static void nullify_header_underline(TNode** header)
{
    (*header)->type = NodeSpan;
    (*header)->head->clear((*header)->head);
    (*header)->head->concat((*header)->head, "<span>");
    (*header)->nesting = false;
}

/* connect node to current anchor */
/* @param builder tree builder */
/* @param node node to connect */
static void connect_to_anchor(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder);
    add_tnode(anchor, *node);
}

/* remove anchor and try on another */
/* @param builder tree builder */
/* @param node node to connect to the tree */
static void return_back(TBuilder* builder, TNode** node)
{
    remove_anchor(builder);
    builder->build_tree(builder, node);
}

/* jump to section, close it and open another */
/* @param builder tree builder */
/* @param node hr node will be connect to body node */
static void close_section(TBuilder* builder, TNode** node)
{
    /* jmp to section */
    while (builder->states->cp > 0)
    {
        remove_anchor(builder);
    }

    TNode* anchor = get_anchor(builder);

    TNode* new_sec = init_tnode(NodeSection, create_string("<section>"), NULL, true);
    add_tnode(anchor->parrent, *node);
    add_tnode(anchor->parrent, new_sec);

    remove_anchor(builder);
    add_anchor(builder, &new_sec);
}

/* in case when we got > 2 spans in row, we wrap them */
/* @param builder tree builder */
/* @param node paragraph's child */
static void wrap_span_to_paragraph(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder);
    TNode* p = init_tnode(NodeParagraph, create_string("<p>"), NULL, true);
    add_tnode(p, get_last_child(anchor));
    add_tnode(p, (*node));
    get_last_child(anchor) = NULL;
    add_tnode(anchor, p);
    add_anchor(builder, &p);
}

/* for default handle */
/* @param builder tree builder */
/* @param node header underline */
static void process_hunderline_node(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder);
    if (anchor->children && get_last_child(anchor)->type == NodeSpan)
    {
        add_tnode(*node, get_last_child(anchor));
        get_last_child(anchor) = NULL;
        add_tnode(anchor, *node);
        return;
    }
    nullify_header_underline(node);
    add_tnode(anchor, *node);
}

/* for default handle */
/* @param builder tree builder */
/* @param node span */
static void process_span_node(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder);
    if (anchor->children && get_last_child(anchor)->type == NodeSpan)
    {
        wrap_span_to_paragraph(builder, node);
        return;
    }
    add_tnode(anchor, *node);
}

/* change state from current to blockquote and after to paragraph */
/* @param builder tree builder */
/* @param node blockquote */
static void switch_to_blockquote(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder);
    add_tnode(anchor, *node);
    TNode* last_bq = *node;
    while (last_bq->children[0]->type == NodeBlockquote)
    {
        last_bq = last_bq->children[0];
    }
    TNode* p = init_tnode(NodeParagraph, create_string("<p>"), NULL, true);
    add_tnode(p, last_bq->children[0]);
    last_bq->children[0] = p;
    p->parrent = last_bq;
    add_anchor(builder, &last_bq);
    add_anchor(builder, &p);
}

/* change state from current to list and after to paragraph */
/* @param builder tree builder */
/* @param node list item */
static void switch_to_list(TBuilder* builder, TNode** node)
{
    add_anchor(builder, node);
    TNode* child = (*node)->children[0];
    if (child->type == NodeBlockquote)
    {
        (*node)->children[0] = NULL;
        switch_to_blockquote(builder, &child);
        return;
    }
    TNode* p = init_tnode(NodeParagraph, create_string("<p>"), NULL, true);
    add_tnode(p, child);
    (*node)->children[0] = NULL;
    add_tnode(*node, p);
    add_anchor(builder, &p);
}

/* grow down in current list */
/* @param builder tree builder */
/* @param node list item */
static inline void add_li_lvl(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder)->parrent;
    add_tnode(get_last_child(anchor), *node);
}

/* in case when we have list with same context */
/* @param builder tree builder */
/* @param node list header */
static inline void combine_lists(TBuilder* builder, TNode** node)
{
    TNode* anchor = get_anchor(builder)->parrent;
    add_tnode(anchor, (*node)->children[0]);
    remove_anchor(builder);
    switch_to_list(builder, &(*node)->children[0]);
    (*node)->children[0] = NULL;
    free_tnode(*node);
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

/* handle global state */
/* @param builder tree builder */
/* @param node current node from parser */
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
        free_tnode(*node);
        break;
    case NodeUOList:
    case NodeOList:
        (*node)->offset = 0;
        TNode* anchor = get_anchor(builder);
        add_tnode(anchor, *node);
        switch_to_list(builder, &(*node)->children[0]);
        break;
    default:
        connect_to_anchor(builder, node);
        break;
    }
}

/* handle codeblock state */
/* @param builder tree builder */
/* @param node current node from parser */
void handle_codeblock(TBuilder* builder, TNode** node)
{
    if ((*node)->type != NodePre)
    {
        TNode* anchor = get_anchor(builder);
        String* code = anchor->children[0]->children[0]->content;
        code->concat(code, builder->raw->text(builder->raw));
    }
    else
    {
        remove_anchor(builder);
    }
    free_tnode(*node);
}

/* handle blockquote state */
/* @param builder tree builder */
/* @param node current node from parser */
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
            TNode* p = init_tnode(NodeParagraph, create_string("<p>"), NULL, true);
            add_tnode(p, new_bq->children[0]);
            new_bq->children[0] = NULL;
            add_tnode(get_anchor(builder), p);
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

/* handle paragraph state */
/* @param builder tree builder */
/* @param node current node from parser */
void handle_paragraph(TBuilder* builder, TNode** node)
{
    switch ((*node)->type)
    {
    case NodeHeadingUnderline:
        nullify_header_underline(node);
    case NodeSpan:
        connect_to_anchor(builder, node);
        return;
    case NodeBreakLine:
        free_tnode(*node);
        remove_anchor(builder);
        return;
    default:
        return_back(builder, node);
        return;
    }
}

/* handle list state */
/* @param builder tree builder */
/* @param node current node from parser */
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
        add_li_lvl(builder, node);
        add_anchor(builder, node);
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

/* attach node to tree depending on the anchor */
static void build_tree(TBuilder* builder, TNode** node)
{
    HANDLE_TABLE[STATE_TABLE[get_anchor(builder)->type]](builder, node);
}

/* initialize tree builder with start anchor */
/* @param builder self structure */
/* @param st_anchor start anchor */
void init_builder(TBuilder* builder, TNode** st_anchor)
{
    builder->states = create_stack(STACK_INITIAL_CAP);
    builder->build_tree = build_tree;
    add_anchor(builder, st_anchor);
}

/* free tree builder */
/* @param builder self structure */
void free_builder(TBuilder* builder)
{
    stack_free(builder->states);
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/