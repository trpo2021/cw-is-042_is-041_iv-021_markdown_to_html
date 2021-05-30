#include <internals/parser/main/parser.h>
#include <internals/renderer/renderer.h>

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

String* render_html(const String* markdown)
{
    TNode* root = parse_document(markdown);
    free_tnode(root);
    return NULL;
}