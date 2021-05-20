#include <internals/parser/main/parser.h>

/* TODO: some refactorng */

/******************************
 *                            *
 *  Section: Helper functions *
 *                            *
 ******************************/

/* split string line by line */
/* @param raw text from document */
/* @param index current index in raw */
/* @return piece of raw splited by \\n */
static String* separate_line(const String* raw, size_t* index)
{
    String* line = init_string(10);

    for (; *index < raw->length(raw); ++(*index))
    {
        line->append(line, raw->get(raw, *index));
        if (raw->get(raw, *index) == '\n' || raw->get(raw, *index) == '\r')
        {
            return line;
        }
    }

    line->append(line, '\n');
    return line;
}

/* wrap node to span node */
/* @param parrent root of line node */
/* @return node wrapped with span node \n */
static TNode* wrap_node(TNode* parrent)
{
    if (parrent->type >= NodeInlineCode && parrent->type <= NodeLink)
    {
        TNode* wrapper = init_tnode(NodeSpan, create_string("<span>"), init_string(10), false);
        add_tnode(wrapper, parrent);
        return wrapper;
    }
    return parrent;
}

/* move the pointer to the last nesting node */
/* @param parrent root of line node */
/* @param cur current anchor in parsing */
static void balance_line_nodes(TNode* parrent, TNode** cur)
{
    if (parrent->nesting)
    {
        *cur = parrent;
        if (parrent->children)
        {
            return balance_line_nodes(parrent->children[0], cur);
        }
    }
}

/* concat span nodes if they go in a row */
/* @param pos_parrent possible span parrent */
/* @param span node for connect */
static void connect_spanes(TNode* pos_parrent, TNode* span)
{
    if (pos_parrent->children)
    {
        TNode* t = get_last_child(pos_parrent);
        if (t->type == NodeSpan)
        {
            t->content->concat(t->content, span->content->text(span->content));
            free_tnode(span);
            return;
        }
    }
    if (pos_parrent->type == NodeSpan && !pos_parrent->children)
    {
        pos_parrent->content->concat(pos_parrent->content, span->content->text(span->content));
        free_tnode(span);
        return;
    }
    add_tnode(pos_parrent, span);
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/

/******************************
 *                            *
 *    Section: Main parser    *
 *                            *
 ******************************/

/* parse current line to AST node */
/* @param perf rule performer without init */
/* @param tokens set of tokens */
/* @param st_pos start position after skip whitespaces */
/* @return node of AST for current line */
static TNode* parse_line(RulePerformer* perf, Array(Token) tokens, size_t st_pos)
{
    init_performer(perf, tokens, st_pos);

    TNode* parrent = wrap_node(perf->invoke(perf, perf->count));
    TNode* cur = parrent;

    balance_line_nodes(parrent, &cur);
    while (perf->cp < perf->count - 1)
    {
        if (perf->mode < ModeAFE)
        {
            perf->cp = skip_spaces(perf->cp, perf->tokens);
        }
        TNode* child = perf->invoke(perf, perf->count);
        balance_line_nodes(parrent, &cur);
        child->type == NodeSpan ? connect_spanes(cur, child) : add_tnode(cur, child);
    }
    return parrent;
}

/* main parser function */
/* @param raw text from document */
/* @return AST root */
TNode* parse_document(const String* raw)
{
    RulePerformer performer;

    TNode* root = init_tnode(NodeBody, create_string("<body>"), NULL, true);
    add_tnode(root, init_tnode(NodeSection, create_string("<section>"), NULL, true));

    TBuilder builder = {0};
    init_builder(&builder, &root->children[0]);

    for (size_t i = 0, st = 0; i < raw->length(raw); ++i, st = 0)
    {
        String* line = separate_line(raw, &i);
        Array(Token) tokens = tokenize(line);

        st = skip_spaces(st, tokens);
        TNode* node = parse_line(&performer, tokens, st);

        builder.raw = line;
        node->offset = st >> 2;
        builder.build_tree(&builder, &node);

        for (size_t j = 0; j < get_array_length(tokens); ++j)
        {
            tokens[j].value->free(tokens[j].value);
        }
        free_array(tokens);
        line->free(line);
    }

    free_builder(&builder);

    return root;
}

/******************************
 *                            *
 *        End section         *
 *                            *
 ******************************/