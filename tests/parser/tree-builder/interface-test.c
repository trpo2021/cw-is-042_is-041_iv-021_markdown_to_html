#include <ctest.h>
#include <internals/parser/main/parser.h>

CTEST(tbuilder, interface)
{
    TBuilder builder = {0};
    TNode* section = init_tnode(NodeSection, NULL, NULL, false);
    init_builder(&builder, &section);
    ASSERT_NOT_NULL(builder.states);
    ASSERT_NOT_NULL(builder.states->anchors);
    ASSERT_EQUAL(10, builder.states->cap);
    ASSERT_EQUAL(0, builder.states->cp);
    free_builder(&builder);
    free_tnode(section);
}