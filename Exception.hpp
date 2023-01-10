/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Exception.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 13:56:50 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 16:50:54 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#pragma once
#include <exception>
#include <string>
#include <stdexcept>


class divide_by_zero: std::logic_error {
public:
    divide_by_zero();
    const char* what() const noexcept;    
    ~divide_by_zero();
};

class virtual_machine_exception: std::exception {
    std::string msg;
    size_t      token_index;
public:
    virtual_machine_exception(std::string const &, size_t);
    virtual ~virtual_machine_exception();
    virtual const char* what() const noexcept;
    size_t get_token_index() const;
};

class not_enough_value_in_stack: public virtual_machine_exception {
public:
    not_enough_value_in_stack(size_t);
    virtual ~not_enough_value_in_stack();
};

class invalid_type: public virtual_machine_exception {
public:
    invalid_type(size_t);
    virtual ~invalid_type();
};

class assert_failed: public virtual_machine_exception {
public:
    assert_failed(size_t);
    virtual ~assert_failed();
};

class invalid_instruction: public virtual_machine_exception {
public:
    invalid_instruction(size_t);
    virtual ~invalid_instruction();
};


