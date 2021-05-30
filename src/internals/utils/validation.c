#include <ctype.h>
#include <internals/utils/validation.h>
#include <stdint.h>
#include <string.h>

static inline void wrap_email(String* email)
{
    sinsert(email, "href=\"mailto:", 0);
    sappend(email, '"');
}

static inline void wrap_url(String* url)
{
    if (strstr(sraw(url), "www.") - sraw(url) == 0)
    {
        sinsert(url, "http://", 0);
    }
    sinsert(url, "href=\"", 0);
    sappend(url, '"');
}

bool is_valid_local(String* local)
{
    for (size_t i = 0; i < slength(local); ++i)
    {
        if (!isalnum(sget(local, i)) && sget(local, i) != '/' && sget(local, i) != '.')
        {
            return false;
        }
    }
    wrap_url(local);
    return true;
}

bool is_valid_url(String* url)
{
    char* valid_start_chunks[] = {"https://", "http://", "www."};
    int32_t start_index = -1;
    char* current_chunk = NULL;
    for (size_t i = 0; i < 3; ++i)
    {
        current_chunk = strstr(sraw(url), valid_start_chunks[i]);
        start_index = current_chunk - sraw(url);
        if (start_index == 0)
        {
            break;
        }
    }
    if (start_index != 0)
    {
        return false;
    }
    for (size_t i = strlen(current_chunk); i < slength(url); ++i)
    {
        if (!isalnum(sget(url, i)) && sget(url, i) != '/' && sget(url, i) != '.')
        {
            return false;
        }
    }
    wrap_url(url);
    return true;
}

bool validate_url(String* content)
{
    return (sget(content, 0) == '/') ? is_valid_local(content) : is_valid_url(content);
}

static bool is_email_valid(String* email)
{
    if (!isalpha(sget(email, 0)))
    {
        return false;
    }
    int32_t at_index = -1, dot_index = -1;
    for (size_t i = 0; i < slength(email); ++i)
    {
        if (isalnum(sget(email, i)))
        {
            continue;
        }
        char c = sget(email, i);
        if (c == '@')
        {
            at_index = i;
        }
        else if (c == '.')
        {
            dot_index = i;
        }
        else
        {
            return false;
        }
    }
    if ((at_index == -1 || dot_index == -1) || (at_index > dot_index))
    {
        return false;
    }
    if (dot_index < slength(email) - 1)
    {
        wrap_email(email);
        return true;
    }
    return false;
}

bool validate_email(String* content)
{
    return is_email_valid(content);
}