/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Compiler.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:58:13 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 17:01:31 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "Scanner.hpp"
#include <iostream>
#include <cinttypes>
#include <vector>


enum Opcode {
    OP_PUSH_i8,
    OP_PUSH_i16,
    OP_PUSH_i32,
    OP_PUSH_f32,
    OP_PUSH_f64,
    OP_POP,

    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MIN,
    OP_MAX,
    OP_AVG,
    OP_AND,
    OP_OR,
    OP_XOR,
    OP_MOD,

    OP_ASSERT,
    OP_PRINT,
    OP_DUMP,
    OP_EXIT,
};

class Compiler
{
private:
    Scanner                     scanner;
    Token                       current;
    Token                       previous;
    std::vector<size_t>         constants_address;
    std::vector<uint8_t>        constants;
    std::vector<Token>          instruction_token;
    std::vector<uint8_t>        instructions;

    bool        panic_mode;
    uint32_t    error_nbr;

    Compiler() = delete;
public:
    Compiler(const Compiler&) = default;
    Compiler& operator=(const Compiler&) = default;
    ~Compiler() = default;

    Compiler(const char *);

    bool    compile();

    std::vector<uint8_t>&   get_instructions();
    std::vector<Token>&     get_instruction_token();

    static void raise_error(const char *message, Token *token);

    class compiler_error: std::invalid_argument {
    public:
        std::string number_of_errs;
        compiler_error(size_t);
        ~compiler_error();
        const char* what() const noexcept;
    };
private:
    void    advance();

    void    write(uint8_t byte, const Token&);
    void    write_constant(const Token&);

    void    skip_sep();

    void    error_current(const char *message);
    void    error_previous(const char *message);
    void    error(const char *message, Token *token);
};
