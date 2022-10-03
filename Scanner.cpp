/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scanner.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 16:06:34 by yfarini           #+#    #+#             */
/*   Updated: 2022/10/03 22:42:32 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Scanner.hpp"

const std::unordered_map<std::string, token_type_t>  Scanner::keywords = {
    {"push",    TOKEN_PUSH},
    {"pop",     TOKEN_POP},
    {"dump",    TOKEN_DUMP},
    {"assert",  TOKEN_ASSERT},
    {"add",     TOKEN_ADD},
    {"sub",     TOKEN_SUB},
    {"mul",     TOKEN_MUL},
    {"div",     TOKEN_DIV},
    {"mod",     TOKEN_MOD},
    {"print",   TOKEN_PRINT},
    {"exit",    TOKEN_EXIT},
    {"int8",    TOKEN_INT8},
    {"int16",   TOKEN_INT16},
    {"int32",   TOKEN_INT32},
    {"float",   TOKEN_FLOAT},
    {"double",  TOKEN_DOUBLE},
};

Scanner::Scanner(const char *_source): source(_source), line(1), current(_source)
{
    curr_line_start = source;
    curr_line_end = get_line_end(curr_line_start);
}


Token Scanner::get_next_token()
{
    skip_non_tokens();
    
    if (reach_end()) return create_token(TOKEN_EOF);

    start = current;
    char c = advance();
    switch (c)
    {
    case '-': return create_token(TOKEN_MINUS);
    case '(': return create_token(TOKEN_OPEN_PARENT);
    case ')': return create_token(TOKEN_CLOSED_PARENT);
    case ';': advance(); return create_token(TOKEN_EO_STDIN);
    case '\n':
        line++;
        curr_line_start = this->current;
        curr_line_end = get_line_end(curr_line_start);
        return create_token(TOKEN_SEP);
    
    default:
        if (isnumber(c)) return number();
        else if (isalpha(c)) return identifier();
        return error("use of unknown charachter");
    }
}

bool    Scanner::reach_end() const
{
    return *current == '\0';
}

char    Scanner::advance()
{
    ++current;
    return current[-1];
}

char    Scanner::peek() const
{
    return current[0];
}

char    Scanner::peek_next() const
{
    if (current[0])
        return current[1];
    return '\0';
}

Token   Scanner::create_token(token_type_t type) const
{
    return (Token) {
        .type = type,
        .line = this->line,
        .start = this->start,
        .length = static_cast<uint32_t>(this->current - this->start),
        .error = NULL,
        .line_start = curr_line_start,
        .line_end = curr_line_end,
    };
}

Token   Scanner::error(const char* message) const
{
    return (Token) {
        .type = TOKEN_ERROR,
        .line = this->line,
        .start = this->start,
        .length = static_cast<uint32_t>(this->current - this->start),
        .error = message,
        .line_start = curr_line_start,
        .line_end = curr_line_end,
    };
}

Token   Scanner::number()
{
    while (isnumber(peek()))
        advance();
    if (peek() == '.')
    {
        advance();
        if (!isnumber(peek()))
            return error("expected digit after `.`");
        while (isnumber(peek()))
            advance();
        return create_token(TOKEN_REAL_NUMBER);
    }
    return create_token(TOKEN_NUMBER);
}

Token   Scanner::identifier()
{
    while (isalnum(peek()))
        advance();
    std::string _identifier(this->start, this->current);
    if (this->keywords.count(_identifier) == 0)
        return error("use of undeclared keyword");
    return create_token(this->keywords.at(_identifier));
}

void    Scanner::skip_non_tokens()
{
    while (skip_whitespace() || skip_comments());
}

bool    Scanner::skip_whitespace()
{
    char c = peek();
    if (c != ' ' && c != '\t')
        return false;
    while ((c = peek()) && (c == ' ' || c == '\t'))
        advance();
    return true;
}

bool    Scanner::skip_comments()
{
    if (peek() == ';' && peek_next() != ';')
    {
        char c;
        while ((c = peek()) && c != '\n')
            advance();
        return true;
    }
    return false;
}

const char  *Scanner::get_line_end(const char *curr) const
{
    while (*curr && *curr != '\n')
        ++curr;
    return curr;
}
