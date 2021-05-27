#include <internals/parser/helpers/rule-performer.h>
#include <internals/parser/helpers/tbuilder.h>
#include <internals/parser/lexer/tokenizer.h>
#include <internals/parser/main/parser.h>

typedef enum
{
    OffsetMultiplier = 2
} ParserConstants;

/******************************
 *                            *
 *  Section: Helper functions *
 *                            *
 ******************************/

static String* separate_line(const String* raw, size_t* index)
{
    String* line = init_string(10);
    for (; *index < raw->length(raw); ++(*index))
    {
        if (raw->get(raw, *index) == '\r')
        {
            continue;
        }
        line->append(line, raw->get(raw, *index));
        if (raw->get(raw, *index) == '\n')
        {
            return line;
        }
    }
    line->append(line, '\n');
    return line;
}

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

static void balance_line(TNode* parrent, TNode** cur)
{
    if (parrent->nesting)
    {
        *cur = parrent;
        if (parrent->children)
        {
            return balance_line(parrent->children[0], cur);
        }
    }
}

static void connect_spanes(TNode* pos_parrent, TNode* span)
{
    TNode* last_child = get_tnode_last_child(pos_parrent);
    if (last_child && last_child->type == NodeSpan)
    {
        last_child->content->concat(last_child->content, span->content->text(span->content));
        free_tnode(span);
        return;
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

static TNode* parse_line(RulePerformer* perf, Array(Token) tokens, size_t st_pos)
{
    init_performer(perf, tokens, st_pos);
    TNode* parrent = wrap_node(perf->invoke(perf, perf->count));
    TNode* cur = parrent;
    balance_line(parrent, &cur);

    while (perf->cp < perf->count - 1)
    {
        if (perf->mode < ModeAvaliableOnlyText)
        {
            perf->cp = skip_spaces(perf->cp, perf->tokens);
        }
        TNode* child = perf->invoke(perf, perf->count);
        balance_line(parrent, &cur);
        child->type == NodeSpan ? connect_spanes(cur, child) : add_tnode(cur, child);
    }

    return parrent;
}

TNode* parse_document(const String* raw)
{
    RulePerformer performer = {0};

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

        builder.raw_text = line;
        node->offset = st >> OffsetMultiplier;
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