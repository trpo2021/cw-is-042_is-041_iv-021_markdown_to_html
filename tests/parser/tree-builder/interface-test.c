#include <ctest.h>
#include <internals/parser/helpers/tbuilder.h>

CTEST(tbuilder, interface)
{
    TBuilder builder = {0};
    TNode* section = init_tnode(NodeSection, NULL, NULL, false);
    init_builder(&builder, &section);
    ASSERT_NOT_NULL(builder.states);
    free_builder(&builder);
    free_tnode(section);
}