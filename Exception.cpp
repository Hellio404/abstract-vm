/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:03:30 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 16:50:32 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "Exception.hpp"

divide_by_zero::divide_by_zero(): std::logic_error("divide by zero") {}

divide_by_zero::~divide_by_zero() {}

const char* divide_by_zero::what() const noexcept 
{
    return "divide by zero";
}


virtual_machine_exception::virtual_machine_exception(std::string const &msg, size_t i): msg(msg), token_index(i) {}
virtual_machine_exception::~virtual_machine_exception() {}
const char* virtual_machine_exception::what() const noexcept { return msg.c_str();}
size_t virtual_machine_exception::get_token_index() const {return token_index;}



not_enough_value_in_stack::not_enough_value_in_stack(size_t i): virtual_machine_exception("stack doesn't contains enough value for operation", i) {}
not_enough_value_in_stack::~not_enough_value_in_stack() {}



invalid_type::invalid_type(size_t i): virtual_machine_exception("Assertion Failed: Type of the top of the stack is not the correct type", i) {}
invalid_type::~invalid_type() {}



assert_failed::assert_failed(size_t i): virtual_machine_exception("Assertion Failed: Value of the top of the stack is not the correct value", i) {}
assert_failed::~assert_failed() {}



invalid_instruction::invalid_instruction(size_t i): virtual_machine_exception("Invalid instruction", i) {}
invalid_instruction::~invalid_instruction() {}