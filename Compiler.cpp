/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Compiler.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:38:34 by yfarini           #+#    #+#             */
/*   Updated: 2022/10/03 22:41:48 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Compiler.hpp"

Compiler::Compiler(const char *_source): scanner(_source), panic_mode(false), error_nbr(0)
{

}

bool    Compiler::compile()
{
    throw std::logic_error("Function not implemented");
}

void    Compiler::advance()
{
    this->previous = this->current;
    this->current = scanner.get_next_token();
}

void    Compiler::match_type(token_type_t type, const char *message)
{
    if (current.type == type)
        advance();
    else
        error_current(message);
}

void    Compiler::error(const char *message, Token *token)
{
    #define RESET   "\033[0m"
    #define BOLDWHITE   "\033[1m\033[37m"
    #define RED     "\033[31m"
    #define GREEN   "\033[32m"

    if (panic_mode) return ;
    panic_mode = true;
    ++error_nbr;

    fprintf(stderr, "\n");
    fprintf(stderr, BOLDWHITE"[Line %d]: " RED "error: " BOLDWHITE "%s\n" RESET,
        token->line, 
        message ? message : token->error
    );

    fprintf(stderr, "%.*s\n", 
        (int)(token->line_end - token->line_start),
        token->line_start
    );
    fprintf(stderr, "%*s", (int)(token->start - token->line_start), "");
    fprintf(stderr, GREEN);
    for (uint32_t i = 0; i < token->length; i++)           
        fprintf(stderr, "^");
    fprintf(stderr, RESET"\n");

    #undef RESET
    #undef BOLDWHITE
    #undef RED
    #undef GREEN
}

void    Compiler::error_current(const char *message)
{
    error(message, &current);
}

void    Compiler::error_previous(const char *message)
{
    error(message, &previous);
}
