/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Compiler.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:58:13 by yfarini           #+#    #+#             */
/*   Updated: 2022/10/03 18:38:29 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Scanner.hpp"
#include <iostream>

class Compiler
{
private:
    Scanner     scanner;
    Token       current;
    Token       previous;

    bool        panic_mode;
    uint32_t    error_nbr;

    Compiler() = delete;
public:
    Compiler(const Compiler&) = default;
    Compiler& operator=(const Compiler&) = default;
    ~Compiler() = default;

    Compiler(const char *);

    bool    compile();
private:
    void    advance();
    void    match_type(token_type_t, const char*);

    void    error(const char *message, Token *token);
    void    error_current(const char *message);
    void    error_previous(const char *message);
};
