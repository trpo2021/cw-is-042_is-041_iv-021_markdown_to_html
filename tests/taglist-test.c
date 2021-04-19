#include <../src/internals/taglist/taglist.h>
#include <ctest.h>
#include <stdio.h>

CTEST(hash, hash_sum_1)
{
    ASSERT_EQUAL_U(98, hashtab_hash("test"));
}

CTEST(hash, hash_sum_2)
{
    ASSERT_EQUAL_U(17, hashtab_hash("# "));
}

CTEST(hash, hash_sum_3)
{
    ASSERT_EQUAL_U(85, hashtab_hash("---"));
}

CTEST(hash, hash_sum_4)
{
    ASSERT_EQUAL_U(66, hashtab_hash(">>>"));
}

CTEST(hash, hash_add)
{
    Tag* map[HASHTAB_SIZE];
    hashtab_init(map);
    hashtab_add(map, "test", "help");
    ASSERT_STR("test", map[98]->key);
}

CTEST(hash, hash_init)
{
    Tag* map[HASHTAB_SIZE];
    hashtab_init(map);
    ASSERT_NULL(map[1]);
}

CTEST(hash, hash_create_1)
{
    Tag* map[HASHTAB_SIZE];
    create_taglist(map);
    ASSERT_STR("# ", map[17]->key);
}

CTEST(hash, hash_create_2)
{
    Tag* map[HASHTAB_SIZE];
    create_taglist(map);
    ASSERT_STR("---", map[85]->key);
}

CTEST(hash, hash_create_3)
{
    Tag* map[HASHTAB_SIZE];
    create_taglist(map);
    ASSERT_STR(">>>", map[66]->key);
}
