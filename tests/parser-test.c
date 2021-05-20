#include <ctest.h>
#include <internals/parser/main/parser.h>

CTEST(parser, headlings)
{
    // fix \t
    String* s = create_string("*** tgg *lol* jhh *** hgkj\n");

    // String* s = create_string("**![*text*]()**");
    /*string s2 = s->Replace(s, "    ", "\t");
    s->Free(s);*/
    TNode* root = parse_document(s);
    free_tnode(root);
    s->free(s);
}