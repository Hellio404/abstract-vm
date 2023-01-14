/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Compiler.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 18:38:34 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/14 16:07:14 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Compiler.hpp"

Compiler::Compiler(const char *_source) : scanner(_source), panic_mode(false), error_nbr(0)
{
}

Compiler::compiler_error::compiler_error(size_t nbr): std::invalid_argument("compiler_error")
{
    this->number_of_errs = std::to_string(nbr);
}

Compiler::compiler_error::~compiler_error() {}

const char* Compiler::compiler_error::what() const noexcept {
    return this->number_of_errs.c_str();
}

bool Compiler::compile()
{
    advance();
    advance();
    while (1)
    {
        skip_sep();
        switch (this->previous.type)
        {
        case TOKEN_PUSH:
            write_constant(this->previous);
            if (this->previous.type != TOKEN_SEP)
                advance();
            break;
        case TOKEN_ASSERT:
        {
            Token token = this->previous;
            write_constant(token);
            if (this->previous.type != TOKEN_SEP)
                advance();
            this->write(OP_ASSERT, token);
            break;
        }
        case TOKEN_POP:
            this->write(OP_POP, this->previous);
            advance();
            break;
        case TOKEN_ADD:
            this->write(OP_ADD, this->previous);
            advance();
            break;
        case TOKEN_SUB:
            this->write(OP_SUB, this->previous);
            advance();
            break;
        case TOKEN_MUL:
            this->write(OP_MUL, this->previous);
            advance();
            break;
        case TOKEN_DIV:
            this->write(OP_DIV, this->previous);
            advance();
            break;
        case TOKEN_MOD:
            this->write(OP_MOD, this->previous);
            advance();
            break;
        case TOKEN_MIN:
            this->write(OP_MIN, this->previous);
            advance();
            break;
        case TOKEN_MAX:
            this->write(OP_MAX, this->previous);
            advance();
            break;
        case TOKEN_AVG:
            this->write(OP_AVG, this->previous);
            advance();
            break;
        case TOKEN_AND:
            this->write(OP_AND, this->previous);
            advance();
            break;
        case TOKEN_OR:
            this->write(OP_OR, this->previous);
            advance();
            break;
        case TOKEN_XOR:
            this->write(OP_XOR, this->previous);
            advance();
            break;
        case TOKEN_PRINT:
            this->write(OP_PRINT, this->previous);
            advance();
            break;
        case TOKEN_ERROR:
            error_previous(NULL);
            break;
        case TOKEN_DUMP:
            this->write(OP_DUMP, this->previous);
            advance();
            break;
        case TOKEN_EXIT:
            this->write(OP_EXIT, this->previous);
            advance();
            goto finish;
        case TOKEN_EOF:
            error_previous("Expected exit before EOF");
            goto leave;
        default:
            error_previous("Invalid token");
            advance();
            break;
        }

        while (this->previous.type != TOKEN_SEP && this->previous.type != TOKEN_EOF)
        {
            error_previous("Expected new line");
            advance();
        }
    }
finish:
    skip_sep();
    if (previous.type != TOKEN_EOF)
        error_previous("Unexpected token after exit");
    // this will change set the real offset of the constants
    for (auto addr : this->constants_address)
    {
        uint64_t offset = (this->instructions[addr] | (this->instructions[addr + 1] << 8)
                        | (this->instructions[addr + 2] << 16) | (this->instructions[addr + 3] << 24));
        offset += this->instructions.size();
        if (offset > UINT32_MAX)
        {
            this->error_nbr++;
            std::cerr << "Error: cannot support more than 4GB of instructions" << std::endl;
            goto leave;
        }
        this->instructions[addr] = offset & 0xFF;
        this->instructions[addr + 1] = (offset >> 8) & 0xFF;
        this->instructions[addr + 2] = (offset >> 16) & 0xFF;
        this->instructions[addr + 3] = (offset >> 24) & 0xFF;
    }
    // this will push the constants at the end of the instruction set
    for (auto c : this->constants)
        this->instructions.push_back(c);
leave:
    if (this->error_nbr > 0)
        throw compiler_error(this->error_nbr);
    return true;
}

void Compiler::skip_sep()
{
    while (this->previous.type == TOKEN_SEP)
    {
        advance();
        panic_mode = false;
    }
}

void Compiler::write(uint8_t byte, const Token& token)
{
    this->instructions.push_back(byte);
    this->instruction_token.push_back(token);
}

void Compiler::write_constant(const Token& token)
{
    if (!(current.type >= TOKEN_INT8 && current.type <= TOKEN_DOUBLE))
        return error_current("Expected a type converter (int8, int16, float...)");
    const token_type_t constant_type = current.type;

    advance();
    if (current.type != TOKEN_OPEN_PARENT)
        return error_previous("Missing '(' for the type converter");

    advance();
    if (constant_type >= TOKEN_FLOAT && current.type != TOKEN_REAL_NUMBER)
        return error_current("Expected a Real Number eg. 0.0");
    else if (constant_type < TOKEN_FLOAT && current.type != TOKEN_NUMBER)
        return error_current("Expected an Integer before this");

    advance();
    if (current.type != TOKEN_CLOSED_PARENT)
        return error_previous("Expected ')' for the type converter after the number");

    this->write(constant_type - TOKEN_INT8 + OP_PUSH_i8, token);
    constants_address.push_back(this->instructions.size());
    this->write(constants.size() & 0xFF, previous);
    this->write((constants.size() >> 8) & 0xFF, previous);
    this->write((constants.size() >> 16) & 0xFF, previous);
    this->write((constants.size() >> 24) & 0xFF, previous);
    constants.insert(constants.end(), previous.start, previous.start + previous.length);
    constants.push_back('\0');

    advance();
}

void Compiler::advance()
{
    this->previous = this->current;
    this->current = scanner.get_next_token();
}

void Compiler::error(const char *message, Token *token)
{
    if (panic_mode)
        return;
    panic_mode = true;
    ++error_nbr;
    Compiler::raise_error(message, token);
}

void Compiler::raise_error(const char *message, Token *token)
{
#define RESET "\033[0m"
#define BOLDWHITE "\033[1m\033[37m"
#define RED "\033[31m"
#define GREEN "\033[32m"
    fprintf(stderr, "\n");
    fprintf(stderr, BOLDWHITE "[Line %d]: " RED "error: " BOLDWHITE "%s\n" RESET,
            token->line,
            message ? message : token->error);

    fprintf(stderr, "%.*s\n",
            (int)(token->line_end - token->line_start),
            token->line_start);
    fprintf(stderr, "%*s", (int)(token->start - token->line_start), "");
    fprintf(stderr, GREEN);
    for (uint32_t i = 0; i < token->length; i++)
        fprintf(stderr, "^");
    fprintf(stderr, RESET "\n");

#undef RESET
#undef BOLDWHITE
#undef RED
#undef GREEN
}

void Compiler::error_current(const char *message)
{
    error(message, &current);
}

void Compiler::error_previous(const char *message)
{
    error(message, &previous);
}


std::vector<uint8_t>&   Compiler::get_instructions()
{
    return this->instructions;
}

std::vector<Token>&     Compiler::get_instruction_token()
{
    return this->instruction_token;
}
