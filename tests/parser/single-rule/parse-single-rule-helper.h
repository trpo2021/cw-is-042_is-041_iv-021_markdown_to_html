#include <internals/memext/memext.h>
#include <internals/parser/helpers/rule-performer.h>
#include <internals/parser/lexer/tokenizer.h>
#include <internals/parser/main/parser.h>
#include <time.h>

__attribute__((unused)) static Array(Token) create_test_data(char* raw)
{
    String* str = screate(raw);
    free(raw);
    sappend(str, '\n');
    Array(Token) arr = tokenize(str);
    sfree(str);
    return arr;
}

__attribute__((unused)) static void free_test_data(Array(Token) data)
{
    for (size_t i = 0; i < get_array_length(data); ++i)
    {
        sfree(data[i].value);
    }
    free_array(data);
}

__attribute__((unused)) static char* generate_sequence_of_terms(const char raw_tokens[], size_t count_of_tokens,
                                                                size_t lim)
{
    char* raw_data = mem_alloc(lim + 1);
    for (size_t i = 0; i < lim; ++i)
    {
        raw_data[i] = raw_tokens[rand() % count_of_tokens];
    }
    raw_data[lim] = 0;
    return raw_data;
}