#include <internals/parser/rule-performer.h>
#include <stdarg.h>

#define PARSE_RULE_FAIL_CODE NULL

/* parse subset of tokens as text */
static inline void parse_text_to_node(RulePerformer* perf, TNode* node, size_t end_pos)
{
    for (; perf->cp < end_pos; ++perf->cp)
    {
        node->content->concat(node->content, get_token_value(perf->tokens[perf->cp]));
    }
}

/* @param perf struct rule performer */
/* @param term set of tokens */
/* @param ignore_spaces if the rule allows spaces */
/* @return length of token sequence */
static inline size_t get_sequence_length(RulePerformer* perf, Term term, bool ignore_spaces)
{
    size_t t_count = 0;
    TypeOfToken type = perf->tokens[perf->cp].type;
    while (is_token_in_term(term, type))
    {
        if (ignore_spaces)
        {
            perf->cp = skip_spaces(perf->cp, perf->tokens);
        }
        type = perf->tokens[perf->cp++].type;
        is_token_in_term(term, type) ? (++t_count) : 0;
    }
    --perf->cp;
    return t_count;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_span(RulePerformer* perf, size_t lim, ...)
{
    TNode* node = init_tnode(NodeSpan, create_string("<span>"), create_string(""), false);
    size_t ws_count = 0;
    for (; perf->cp < lim && !perf->tokens[perf->cp].op; ++perf->cp)
    {
        is_token_in_term(WHITESPACE_TERM, perf->tokens[perf->cp].type) ? (++ws_count) : (ws_count = 0);
        node->content->concat(node->content, get_token_value(perf->tokens[perf->cp]));
    }
    if (is_token_in_term(BR_TERM, perf->tokens[perf->cp].type))
    {
        if (ws_count >= 2)
        {
            add_tnode(node, init_tnode(NodeBreakLine, create_string("<br>"), NULL, false));
            node->nesting = true;
        }
        perf->cp = perf->count;
    }
    return node;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_hr_rule(RulePerformer* perf, size_t lim, ...)
{
    size_t t_count = get_sequence_length(perf, HR_TERM, true);
    if (is_token_in_term(BR_TERM, perf->tokens[perf->cp].type) && t_count >= 3)
    {
        perf->cp = perf->count;
        return init_tnode(NodeHorizontalLine, create_string("<hr/>"), NULL, false);
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_br_rule(RulePerformer* perf, size_t lim, ...)
{
    perf->cp = perf->count;
    return init_tnode(NodeBreakLine, create_string("<br>"), NULL, false);
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_header_underline_rule(RulePerformer* perf, size_t lim, ...)
{
    va_list args;
    va_start(args, lim);
    TypeOfRule rule = va_arg(args, TypeOfRule);
    va_end(args);
    size_t backup = perf->cp;
    size_t t_count = get_sequence_length(perf, rule == RuleH1Underline ? H1U_TERM : H2U_TERM, false);
    if (is_token_in_term(BR_TERM, perf->tokens[perf->cp].type) && t_count > 1)
    {
        String* head = rule == RuleH1Underline ? create_string("<h1>") : create_string("<h2>");
        TNode* node = init_tnode(NodeHeadingUnderline, head, create_string(""), true);
        for (size_t i = backup; i < perf->cp; ++i)
        {
            node->content->concat(node->content, get_token_value(perf->tokens[i]));
        }
        perf->cp = perf->count;
        return node;
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_precode_rule(RulePerformer* perf, size_t lim, ...)
{
    size_t t_count = get_sequence_length(perf, CODE_TERM, false);
    perf->cp = skip_spaces(perf->cp, perf->tokens);
    if (is_token_in_term(BR_TERM, perf->tokens[perf->cp].type) && t_count > 2)
    {
        TNode* parrent = init_tnode(NodePre, create_string("<pre>"), NULL, true);
        add_tnode(parrent, init_tnode(NodeCode, create_string("<code>"), NULL, true));
        add_tnode(parrent->children[0], init_tnode(NodeSpan, create_string("<span>"), create_string(""), false));
        perf->cp = perf->count;
        return parrent;
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_list_rule(RulePerformer* perf, size_t lim, ...)
{
    va_list args;
    va_start(args, lim);
    TypeOfRule rule = va_arg(args, TypeOfRule);
    va_end(args);
    if (is_token_in_term(WHITESPACE_TERM, perf->tokens[++perf->cp].type))
    {
        TNode* parrent;
        if (rule == RuleUOList)
        {
            parrent = init_tnode(NodeUOList, create_string("<ul>"), NULL, true);
        }
        else
        {
            parrent = init_tnode(NodeOList, create_string("<ol>"), NULL, true);
        }
        add_tnode(parrent, init_tnode(NodeListItem, create_string("<li>"), NULL, true));
        return parrent;
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_blockquote_rule(RulePerformer* perf, size_t lim, ...)
{
    size_t t_count = get_sequence_length(perf, BLOCKQUOTE_TERM, true);
    if (!is_token_in_term(BR_TERM, perf->tokens[perf->cp].type) && t_count <= 15)
    {
        TNode* parrent = init_tnode(NodeBlockquote, create_string("<blockquote>"), NULL, true);
        TNode* tmp = parrent;
        for (size_t i = 1; i < t_count; ++i)
        {
            add_tnode(tmp, init_tnode(NodeBlockquote, create_string("<blockquote>"), NULL, true));
            tmp = tmp->children[0];
        }
        return parrent;
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_hinline_rule(RulePerformer* perf, size_t lim, ...)
{
    size_t t_count = get_sequence_length(perf, HI_TERM, false);
    if (is_token_in_term(WHITESPACE_TERM, perf->tokens[perf->cp].type))
    {
        if (t_count > 0 && t_count < 7)
        {
            String* head = create_string("<h");
            head->append(head, (char)(t_count + '0'));
            head->append(head, '>');
            return init_tnode(NodeHeadingInline, head, NULL, true);
        }
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_code_rule(RulePerformer* perf, size_t lim, ...)
{
    size_t t_count = get_sequence_length(perf, CODE_TERM, true);
    size_t end_pos = find_end_pos(perf, lim, CODE_TERM, t_count);
    if (end_pos > perf->cp)
    {
        TNode* parrent = init_tnode(NodeInlineCode, create_string("<code>"), NULL, true);
        TNode* text = init_tnode(NodeSpan, create_string("<span>"), create_string(""), false);
        parse_text_to_node(perf, text, end_pos - t_count + 1);
        add_tnode(parrent, text);
        perf->cp = end_pos + 1;
        return parrent;
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_alink_rule(RulePerformer* perf, size_t lim, ...)
{
    ++perf->cp;
    size_t end_pos = find_end_pos(perf, lim, ALINK_END_TERM, 1);
    if (end_pos > perf->cp)
    {
        TNode* parrent = init_tnode(NodeLink, create_string("<a>"), NULL, true);
        TNode* src = init_tnode(NodeSrc, create_string("<src>"), create_string(""), false);
        parse_text_to_node(perf, src, end_pos);
        add_tnode(parrent, src);
        perf->cp = end_pos + 1;
        return parrent;
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_link_rule(RulePerformer* perf, size_t lim, ...)
{
    size_t backup = perf->cp;
    size_t end_sq_pos = find_end_pos(perf, lim, LINK_END_FIRST_TERM, 1);
    if (end_sq_pos > perf->cp)
    {
        if (perf->tokens[end_sq_pos + 1].type == TokenOPBracket)
        {
            perf->cp = end_sq_pos + 1;
            size_t end_df_pos = find_end_pos(perf, lim, LINK_END_LAST_TERM, 1);
            if (end_df_pos > perf->cp)
            {
                TNode* parrent = init_tnode(NodeLink, create_string("<a>"), NULL, true);
                TNode* alt = init_tnode(NodeAlt, create_string("<alt>"), NULL, false);
                TNode* src = init_tnode(NodeSrc, create_string("<src>"), create_string(""), false);
                add_tnode(parrent, alt);
                add_tnode(parrent, src);
                perf->cp = backup + 1;
                while (perf->cp < end_sq_pos)
                {
                    add_tnode(alt, perf->invoke(perf, end_sq_pos));
                }
                perf->cp = end_sq_pos + 2;
                parse_text_to_node(perf, src, end_df_pos);
                perf->cp = end_df_pos + 1;
                return parrent;
            }
        }
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_img_rule(RulePerformer* perf, size_t lim, ...)
{
    if (perf->tokens[++perf->cp].type == TokenOPSquareBracket)
    {
        TNode* link = parse_link_rule(perf, lim);
        if (link)
        {
            TNode* img = init_tnode(NodeImage, create_string("<img>"), NULL, false);
            add_tnode(img, link);
            return img;
        }
    }
    return PARSE_RULE_FAIL_CODE;
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @param ... TypeOfRule using if function can parse set of rules with same algorithm */
/* @return node from parsed rule or NULL if parse failed */
static TNode* parse_empasis_rule(RulePerformer* perf, size_t lim, ...)
{
    size_t t_count = get_sequence_length(perf, EMPHASIS_TERM, false);
    size_t end_pos = find_end_pos(perf, lim, EMPHASIS_TERM, t_count);
    if (end_pos > perf->cp)
    {
        size_t offset = t_count;
        TNode* parrent = init_tnode(NodeEmphasis, create_string((t_count > 1) ? "<strong>" : "<em>"), NULL, true);
        t_count -= (t_count > 1) ? 2 : 1;
        TNode* tmp = parrent;
        while (t_count > 1)
        {
            add_tnode(tmp, init_tnode(NodeEmphasis, create_string("<strong>"), NULL, true));
            tmp = tmp->children[0];
            t_count -= 2;
        }
        if (t_count == 1)
        {
            add_tnode(tmp, init_tnode(NodeEmphasis, create_string("<em>"), NULL, true));
            tmp = tmp->children[0];
        }
        while (perf->cp < end_pos - offset + 1)
        {
            add_tnode(tmp, perf->invoke(perf, end_pos - offset + 1));
        }
        perf->cp = end_pos + 1;
        return parrent;
    }
    return PARSE_RULE_FAIL_CODE;
}

typedef struct
{
    TNode* (*parse_rule)(RulePerformer* perf, size_t lim, ...);
} Rule;

typedef struct
{
    TypeOfRule rules[5];
} SelectionTable;

static const SelectionTable RULE_TABLE[] = {
    [TokenLineBreak] = {{RuleLineBreak, RuleUnknown}},
    [TokenUnderscore] = {{RuleHorizontalLine, RuleEmphasis, RuleUnknown}},
    [TokenAsterisk] = {{RuleHorizontalLine, RuleUOList, RuleEmphasis, RuleUnknown}},
    [TokenGraveAccent] = {{RuleCodeBlock, RuleCodeInline, RuleUnknown}},
    [TokenEquals] = {{RuleH1Underline, RuleUnknown}},
    [TokenMinus] = {{RuleH2Underline, RuleUOList, RuleUnknown}},
    [TokenPlus] = {{RuleUOList, RuleUnknown}},
    [TokenOPAngleBracket] = {{RuleAutoLink, RuleUnknown}},
    [TokenLattice] = {{RuleHeadingInline, RuleUnknown}},
    [TokenExclamationMark] = {{RuleImage, RuleUnknown}},
    [TokenOPSquareBracket] = {{RuleLink, RuleUnknown}},
    [TokenCLAngleBracket] = {{RuleBlockquote, RuleUnknown}},
    [TokenNumber] = {{RuleOList, RuleUnknown}},
};

static const Rule PARSE_TABLE[] = {[RuleHorizontalLine] = {parse_hr_rule},
                                   [RuleLineBreak] = {parse_br_rule},
                                   [RuleH1Underline] = {parse_header_underline_rule},
                                   [RuleH2Underline] = {parse_header_underline_rule},
                                   [RuleCodeBlock] = {parse_precode_rule},
                                   [RuleOList] = {parse_list_rule},
                                   [RuleUOList] = {parse_list_rule},
                                   [RuleBlockquote] = {parse_blockquote_rule},
                                   [RuleHeadingInline] = {parse_hinline_rule},
                                   [RuleEmphasis] = {parse_empasis_rule},
                                   [RuleCodeInline] = {parse_code_rule},
                                   [RuleImage] = {parse_img_rule},
                                   [RuleLink] = {parse_link_rule},
                                   [RuleAutoLink] = {parse_alink_rule},
                                   [RuleUnknown] = {parse_span}};

/* @param rule parsed rule */
/* @return mode depending on the rule */
static RPMode change_mode(TypeOfRule rule)
{
    if (rule < RuleOList)
    {
        return ModeAFL;
    }
    else if (rule < RuleBlockquote)
    {
        return ModeAFB;
    }
    else if (rule < RuleHeadingInline)
    {
        return ModeAFH;
    }
    return ModeAFE;
}

/* @param t current token type */
/* @param attempt attempt number aka index in SelectionTable */
/* @return rule depending on the token and attempt */
static TypeOfRule try_get_rule(TypeOfToken t, int32_t attempt)
{
    return RULE_TABLE[t].rules[attempt];
}

/* @param perf struct rule performer */
/* @param lim limit for parse */
/* @return node from block of tokens, can't be NULL */
static TNode* execute(RulePerformer* perf, size_t lim)
{
    if (!perf->tokens[perf->cp].op)
    {
        perf->mode = ModeAFE;
        return PARSE_TABLE[RuleUnknown].parse_rule(perf, lim);
    }
    TNode* node = NULL;
    TypeOfToken t = perf->tokens[perf->cp].type;
    int32_t attempt = 0;
    size_t backup = perf->cp;
    while (!node)
    {
        perf->cp = backup;
        TypeOfRule rule = try_get_rule(t, attempt++);
        if ((int32_t)rule < (int32_t)perf->mode)
        {
            continue;
        }
        if (rule == RuleUnknown)
        {
            perf->tokens[perf->cp].op = false;
        }
        node = PARSE_TABLE[rule].parse_rule(perf, lim, rule);
        perf->mode = change_mode(rule);
    }
    return node;
}

void init_performer(RulePerformer* perf, Array(Token) tokens, size_t pos)
{
    perf->mode = tokens[pos].op ? ModeAAL : ModeAFE;
    perf->tokens = tokens;
    perf->cp = pos;
    perf->count = get_array_length(tokens);
    perf->invoke = &execute;
}