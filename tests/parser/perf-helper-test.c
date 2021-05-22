#include <ctest.h>
#include <internals/parser/main/parser.h>

CTEST(rp_help, skip_spaces_skip_case)
{
    String* str = create_string("   start from 3\n");
    Array(Token) arr = tokenize(str);

    ASSERT_EQUAL(3, skip_spaces(0, arr));

    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        arr[i].value->free(arr[i].value);
    }
    free_array(arr);
    str->free(str);
}

CTEST(rp_help, skip_spaces_wo_spaces_case)
{
    String* str = create_string("start from zero\n");
    Array(Token) arr = tokenize(str);

    ASSERT_EQUAL(0, skip_spaces(0, arr));

    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        arr[i].value->free(arr[i].value);
    }
    free_array(arr);
    str->free(str);
}

CTEST(rp_help, find_end_pos_default)
{
    String* str = create_string("**some bold text**\n");
    Array(Token) arr = tokenize(str);

    RulePerformer perf = {.tokens = arr, .count = get_array_length(arr), .cp = 2};

    ASSERT_EQUAL(8, find_end_pos(&perf, perf.count, EMPHASIS_TERM, 2));

    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        arr[i].value->free(arr[i].value);
    }
    free_array(arr);
    str->free(str);
}

CTEST(rp_help, find_end_pos_wo_spaces)
{
    String* str = create_string("****\n");
    Array(Token) arr = tokenize(str);

    RulePerformer perf = {.tokens = arr, .count = get_array_length(arr), .cp = 2};

    ASSERT_EQUAL(3, find_end_pos(&perf, perf.count, EMPHASIS_TERM, 2));

    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        arr[i].value->free(arr[i].value);
    }
    free_array(arr);
    str->free(str);
}

CTEST(rp_help, find_end_pos_fail)
{
    String* str = create_string("without emphasis\n");
    Array(Token) arr = tokenize(str);

    RulePerformer perf = {.tokens = arr, .count = get_array_length(arr), .cp = 0};

    ASSERT_EQUAL(0, find_end_pos(&perf, perf.count, EMPHASIS_TERM, 2));

    for (size_t i = 0; i < get_array_length(arr); ++i)
    {
        arr[i].value->free(arr[i].value);
    }
    free_array(arr);
    str->free(str);
}

CTEST(rp_help, token_belongs_hr_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenUnderscore || t == TokenAsterisk)
        {
            ASSERT_TRUE(is_token_in_term(HR_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(HR_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_br_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenLineBreak)
        {
            ASSERT_TRUE(is_token_in_term(BR_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(BR_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_h1u_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenEquals)
        {
            ASSERT_TRUE(is_token_in_term(H1U_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(H1U_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_h2u_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenMinus)
        {
            ASSERT_TRUE(is_token_in_term(H2U_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(H2U_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_code_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenGraveAccent)
        {
            ASSERT_TRUE(is_token_in_term(CODE_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(CODE_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_olist_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenNumber)
        {
            ASSERT_TRUE(is_token_in_term(OLIST_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(OLIST_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_uolist_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenAsterisk || t == TokenMinus || t == TokenPlus)
        {
            ASSERT_TRUE(is_token_in_term(UOLIST_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(UOLIST_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_bq_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenCLAngleBracket)
        {
            ASSERT_TRUE(is_token_in_term(BLOCKQUOTE_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(BLOCKQUOTE_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_hi_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenLattice)
        {
            ASSERT_TRUE(is_token_in_term(HI_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(HI_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_link_end_first_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenCLSquareBracket)
        {
            ASSERT_TRUE(is_token_in_term(LINK_END_FIRST_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(LINK_END_FIRST_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_link_end_last_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenCLBracket)
        {
            ASSERT_TRUE(is_token_in_term(LINK_END_LAST_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(LINK_END_LAST_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_alink_end_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenCLAngleBracket)
        {
            ASSERT_TRUE(is_token_in_term(ALINK_END_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(ALINK_END_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_link_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenOPSquareBracket)
        {
            ASSERT_TRUE(is_token_in_term(LINK_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(LINK_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_img_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenExclamationMark)
        {
            ASSERT_TRUE(is_token_in_term(IMG_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(IMG_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_emphasis_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenUnderscore || t == TokenAsterisk)
        {
            ASSERT_TRUE(is_token_in_term(EMPHASIS_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(EMPHASIS_TERM, t));
        }
    }
}

CTEST(rp_help, token_belongs_space_term)
{
    for (TypeOfToken t = TokenLineBreak; t <= TokenText; ++t)
    {
        if (t == TokenSpace)
        {
            ASSERT_TRUE(is_token_in_term(WHITESPACE_TERM, t));
        }
        else
        {
            ASSERT_FALSE(is_token_in_term(WHITESPACE_TERM, t));
        }
    }
}