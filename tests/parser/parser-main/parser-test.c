#include <ctest.h>
#include <internals/parser/main/parser.h>

/* TODO: add tests for parser */
CTEST(parser, tmp)
{
    // fix \t
    String* s = create_string("* lvl 0\n"
                              "    + `lvl 1`\n"
                              "    1. not lvl 2\n"
                              "        1. lvl 2\n"
                              "    ````\n"
                              " code lol???\n"
                              "``````\n"
                              "=====\n");
    TNode* root = parse_document(s);
    ASSERT_NOT_NULL(root);
    free_tnode(root);
    s->free(s);
}