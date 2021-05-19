#include <internals/parser/rule-performer.h>

static Array(Token) create_test_data(char* raw)
{
    String* str = create_string(raw);
    free(raw);
    str->append(str, '\n');
    Array(Token) arr = tokenize(str);
    str->free(str);
    return arr;
}

static void free_test_data(Array(Token) data)
{
    for (size_t i = 0; i < get_array_length(data); ++i)
    {
        data[i].value->free(data[i].value);
    }
    free_array(data);
}

static char* generate_sequence_of_terms(const char raw_tokens[], size_t count_of_tokens, size_t lim)
{
    char* raw_data = malloc(lim + 1);
    for (size_t i = 0; i < lim; i++)
    {
        raw_data[i] = raw_tokens[rand() % count_of_tokens];
    }
    raw_data[lim] = 0;
    return raw_data;
}