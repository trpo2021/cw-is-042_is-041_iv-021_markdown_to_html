#include <ctest.h>
#include <internals/utils/validation.h>
#include <stdio.h>

CTEST(validation, email_correct)
{
    String* email = screate("azbuka@gmail.com");
    ASSERT_TRUE(validate_email(email));
    sfree(email);
}

CTEST(validation, email_without_dot)
{
    String* email = screate("azbuka@gmail");
    ASSERT_FALSE(validate_email(email));
    sfree(email);
}

CTEST(validation, email_end_on_dot)
{
    String* email = screate("azbuka@gmail.");
    ASSERT_FALSE(validate_email(email));
    sfree(email);
}

CTEST(validation, email_without_at)
{
    String* email = screate("azbukagmail.com");
    ASSERT_FALSE(validate_email(email));
    sfree(email);
}

CTEST(validation, email_end_on_at)
{
    String* email = screate("azbuka@");
    ASSERT_FALSE(validate_email(email));
    sfree(email);
}

CTEST(validation, email_at_after_dot)
{
    String* email = screate("azbuka.gmail@");
    ASSERT_FALSE(validate_email(email));
    sfree(email);
}

CTEST(validation, email_with_incorrect_characters)
{
    String* email = screate("$$#azbuka.gmai^l@");
    ASSERT_FALSE(validate_email(email));
    sfree(email);
}

CTEST(validation, url_https_correct)
{
    String* url = screate("https://habr.com");
    ASSERT_TRUE(validate_url(url));
    sfree(url);
}

CTEST(validation, url_https_incorrect)
{
    String* url = screate("https:/habr.com");
    ASSERT_FALSE(validate_url(url));
    sfree(url);
}

CTEST(validation, url_http_correct)
{
    String* url = screate("http://habr.com");
    ASSERT_TRUE(validate_url(url));
    sfree(url);
}

CTEST(validation, url_http_incorrect)
{
    String* url = screate("http:/habr.com");
    ASSERT_FALSE(validate_url(url));
    sfree(url);
}

CTEST(validation, url_local_correct)
{
    String* url = screate("/assets/img.png");
    ASSERT_TRUE(validate_url(url));
    sfree(url);
}

CTEST(validation, url_local_incorrect)
{
    String* url = screate("assets/img.png");
    ASSERT_FALSE(validate_url(url));
    sfree(url);
}