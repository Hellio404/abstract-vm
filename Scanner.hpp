/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Scanner.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:39:06 by yfarini           #+#    #+#             */
/*   Updated: 2022/10/11 23:19:17 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <cinttypes>
# include <string>
# include <unordered_map>

typedef enum token_type {
    TOKEN_PUSH,
    TOKEN_POP,
    TOKEN_DUMP,
    TOKEN_ASSERT,
    TOKEN_PRINT,
    TOKEN_EXIT,

    TOKEN_ADD,
    TOKEN_SUB,
    TOKEN_MUL,
    TOKEN_DIV,
    TOKEN_MOD,

    TOKEN_INT8,
    TOKEN_INT16,
    TOKEN_INT32,
    TOKEN_FLOAT,
    TOKEN_DOUBLE,

    TOKEN_OPEN_PARENT,
    TOKEN_CLOSED_PARENT,

    TOKEN_MINUS,
    TOKEN_NUMBER,
    TOKEN_REAL_NUMBER,

    TOKEN_ERROR,
    TOKEN_SEP,
    TOKEN_EOF,
    TOKEN_EO_STDIN,
}           token_type_t;

struct Token {
    token_type_t    type;
    uint32_t        line;
    const char      *line_start;
    const char      *line_end;
    const char      *start;
    const char      *error;
    uint32_t        length;

    Token() = default;
    ~Token() = default;
    Token(const Token&) = default;
    Token& operator=(const Token&) = default;
};

class Scanner
{
private:
    const char          *source;
    uint32_t            line;
    // the start of the line being parsed
    const char          *curr_line_start;
    const char          *curr_line_end;
    // the start of the current token being parsed
    const char          *start;
    // the next characted needed to be parsed
    const char          *current;

    // map each known keyword to a token_type
    static const std::unordered_map<std::string, token_type_t>  keywords;
public:
    Scanner() = delete;
    ~Scanner() = default;
    Scanner(const Scanner&) = default;
    Scanner& operator =(const Scanner&) = default;

    Scanner(const char *);
    Token   get_next_token();
private:

    bool    reach_end() const;
    // return the next character and increment `this->current`
    char    advance();
    // return the next character without incrementing `this->current`
    char    peek() const;
    // return the  character after the next one without incrementing `this->current`
    char    peek_next() const;

    // given a type of a token, create a token with start = `this->start` and length of `this->current - this->start`
    Token   create_token(token_type_t) const;
    // given an error message create a token of type TOKEN_ERROR and set it's error field to the given error message
    Token   error(const char* message) const;
    // read a number (int or float) and return a token of type TOKEN_NUMBER or TOKEN_REAL_NUMBER depending on if the number is a floating point
    Token   number();
    // read an identifier, if it's an known keyword return it's type as the token type if not return a token of type error
    Token   identifier();

    void    skip_non_tokens();
    bool    skip_whitespace();
    bool    skip_comments();

    const char  *get_line_end(const char *) const;
};
