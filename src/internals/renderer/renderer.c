#include <internals/collection/collection.h>
#include <internals/parser/main/parser.h>
#include <internals/renderer/renderer.h>

typedef struct _renderer
{
    String* html;
    void (*render_ast)(struct _renderer* renderer, TNode* ast_node);
} Renderer;

static inline void close_tag(String* doc, String* node_head)
{
    sinsert(node_head, "/", 1);
    sconcat(doc, sraw(node_head));
}

static inline void format_doc(String* doc, TNode* node)
{
    for (size_t i = 0; i < get_tnode_lvl(node); ++i)
    {
        sconcat(doc, " ");
    }
}

static inline void add_next_line(String* doc)
{
    sconcat(doc, "\n");
}

static inline void replace_keywords(String* html, String* source)
{
    String* replaced = sreplace(source, "&lt;", "<");
    String* temp = replaced;
    replaced = sreplace(replaced, "&gt;", ">");
    sfree(temp);
    sconcat(html, sraw(replaced));
    sfree(replaced);
}

static inline void render_horizontal_line(Renderer* renderer, TNode* node)
{
    format_doc(renderer->html, node);
    sconcat(renderer->html, sraw(node->head));
    add_next_line(renderer->html);
}

static inline void render_break_line(Renderer* renderer, TNode* node)
{
    if (get_array_length(node->parrent->parrent->children) > 1)
    {
        add_next_line(renderer->html);
        format_doc(renderer->html, node);
        sconcat(renderer->html, sraw(node->head));
        return;
    }
    sconcat(renderer->html, sraw(node->head));
}

static inline void render_text(Renderer* renderer, TNode* node)
{
    if (scontains(node->content, "<") || scontains(node->content, ">"))
    {
        replace_keywords(renderer->html, node->content);
    }
    else
    {
        sconcat(renderer->html, sraw(node->content));
    }
    for (size_t i = 0; i < get_array_length(node->children); ++i)
    {
        renderer->render_ast(renderer, node->children[i]);
    }
}

static inline void render_inline_tag(Renderer* renderer, TNode* node)
{
    sconcat(renderer->html, sraw(node->head));
    for (size_t i = 0; i < get_array_length(node->children); ++i)
    {
        renderer->render_ast(renderer, node->children[i]);
    }
    close_tag(renderer->html, node->head);
}

static void render_default(Renderer* renderer, TNode* node)
{
    format_doc(renderer->html, node);
    sconcat(renderer->html, sraw(node->head));
    add_next_line(renderer->html);
    for (size_t i = 0; i < get_array_length(node->children); ++i)
    {
        renderer->render_ast(renderer, node->children[i]);
    }
    format_doc(renderer->html, node);
    close_tag(renderer->html, node->head);
    add_next_line(renderer->html);
}

static void render_wrapper(Renderer* renderer, TNode* node)
{
    format_doc(renderer->html, node);
    sconcat(renderer->html, sraw(node->head));
    if (get_array_length(node->children) > 1)
    {
        add_next_line(renderer->html);
        for (size_t i = 0; i < get_array_length(node->children); ++i)
        {
            format_doc(renderer->html, node->children[i]);
            renderer->render_ast(renderer, node->children[i]);
            add_next_line(renderer->html);
        }
        format_doc(renderer->html, node);
        close_tag(renderer->html, node->head);
        add_next_line(renderer->html);
        return;
    }
    for (size_t i = 0; i < get_array_length(node->children); ++i)
    {
        renderer->render_ast(renderer, node->children[i]);
    }
    close_tag(renderer->html, node->head);
    add_next_line(renderer->html);
}

static void render_header(Renderer* renderer, TNode* node)
{
    if (node->parrent->type != NodeSpan)
    {
        format_doc(renderer->html, node);
    }
    sconcat(renderer->html, sraw(node->head));
    for (size_t i = 0; i < get_array_length(node->children); ++i)
    {
        renderer->render_ast(renderer, node->children[i]);
    }
    close_tag(renderer->html, node->head);
    if (node->parrent->type != NodeSpan)
    {
        add_next_line(renderer->html);
    }
}

static void render_codeblock(Renderer* renderer, TNode* node)
{
    format_doc(renderer->html, node);
    sconcat(renderer->html, sraw(node->head));
    add_next_line(renderer->html);
    size_t length = 0;
    String** lines = ssplit(node->children[0]->content, "\n", &length);
    for (size_t i = 0; i < length; ++i)
    {
        format_doc(renderer->html, node->children[0]);
        if (scontains(lines[i], "<") || scontains(lines[i], ">"))
        {
            replace_keywords(renderer->html, lines[i]);
        }
        else
        {
            sconcat(renderer->html, sraw(lines[i]));
        }
        add_next_line(renderer->html);
        sfree(lines[i]);
    }
    free(lines);
    format_doc(renderer->html, node);
    close_tag(renderer->html, node->head);
    add_next_line(renderer->html);
}

static inline void render_src_link(Renderer* renderer, TNode* node)
{
    String* head = scopy(node->head);
    if (slength(node->children[0]->content) > 0)
    {
        sinsert(head, " ", slength(head) - 1);
    }
    sinsert(head, sraw(node->children[0]->content), slength(head) - 1);
    sconcat(renderer->html, sraw(head));
    sfree(head);
}

static void render_link(Renderer* renderer, TNode* node)
{
    render_src_link(renderer, node);
    if (get_array_length(node->children) == 1)
    {
        sconcat(renderer->html, sraw(node->content));
        close_tag(renderer->html, node->head);
        return;
    }
    for (size_t i = 0; i < get_array_length(node->children[1]->children); ++i)
    {
        renderer->render_ast(renderer, node->children[1]->children[i]);
    }
    close_tag(renderer->html, node->head);
}

static void render_img(Renderer* renderer, TNode* node)
{
    String* head = scopy(node->head);
    String* link_src = sreplace(node->children[0]->children[0]->content, "src", "href");
    if (slength(link_src) > 0)
    {
        sinsert(head, " ", slength(head) - 1);
    }
    sinsert(head, sraw(link_src), slength(head) - 1);
    if (slength(node->children[0]->children[1]->content) > 0)
    {
        sinsert(head, " alt=\"\"", slength(head) - 1);
    }
    sinsert(head, sraw(node->children[0]->children[1]->content), slength(head) - 2);
    sconcat(renderer->html, sraw(head));
    sfree(head);
    sfree(link_src);
}

static void choose_strategy(Renderer* renderer, TNode* ast_node)
{
    switch (ast_node->type)
    {
    case NodeHeadingInline:
        render_header(renderer, ast_node);
        break;
    case NodeParagraph:
        render_wrapper(renderer, ast_node);
        break;
    case NodeSpan:
        render_text(renderer, ast_node);
        break;
    case NodeHorizontalLine:
        render_horizontal_line(renderer, ast_node);
        break;
    case NodeBreakLine:
        render_break_line(renderer, ast_node);
        break;
    case NodeLink:
        render_link(renderer, ast_node);
        break;
    case NodeImage:
        render_img(renderer, ast_node);
        break;
    case NodeInlineCode:
    case NodeEmphasis:
        render_inline_tag(renderer, ast_node);
        break;
    case NodeCode:
        render_codeblock(renderer, ast_node);
        break;
    default:
        render_default(renderer, ast_node);
        break;
    }
}

String* render_html(const String* markdown)
{
    String* replaced = sreplace(markdown, "    ", "\t");
    sconcat(replaced, "\n\n");
    Renderer renderer = {.html = sinit(scapacity(replaced)), .render_ast = choose_strategy};
    TNode* root = parse_document(replaced);
    renderer.render_ast(&renderer, root);
    free_tnode(root);
    sfree(replaced);
    return renderer.html;
}