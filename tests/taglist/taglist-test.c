#include <ctest.h>
#include <internals/taglist/taglist.h>
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
    hashtab_delete(map, "test");
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
    delete_taglist(map);
}

CTEST(hash, hash_create_2)
{
    Tag* map[HASHTAB_SIZE];
    create_taglist(map);
    ASSERT_STR("---", map[85]->key);
    delete_taglist(map);
}

CTEST(hash, hash_create_3)
{
    Tag* map[HASHTAB_SIZE];
    create_taglist(map);
    ASSERT_STR(">>>", map[66]->key);
    delete_taglist(map);
}

CTEST(hash, hash_lookup_1)
{
    Tag* map[HASHTAB_SIZE];
    create_taglist(map);
    ASSERT_NOT_NULL(hashtab_lookup(map, "### "));
    delete_taglist(map);
}

CTEST(hash, hash_lookup_2)
{
    Tag* map[HASHTAB_SIZE];
    create_taglist(map);
    ASSERT_NOT_NULL(hashtab_lookup(map, "  \n"));
    delete_taglist(map);
}

CTEST(hash, hash_delete_1)
{
    Tag* map[HASHTAB_SIZE];
    create_taglist(map);
    hashtab_delete(map, "1)");
    ASSERT_NULL(hashtab_lookup(map, "1)"));
    delete_taglist(map);
}

CTEST(hash, hash_delete_2)
{
    Tag* map[HASHTAB_SIZE];
    create_taglist(map);
    hashtab_delete(map, "---");
    ASSERT_NULL(hashtab_lookup(map, "---"));
    delete_taglist(map);
}