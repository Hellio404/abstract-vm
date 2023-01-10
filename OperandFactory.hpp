/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:47:44 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/09 12:47:45 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "IOperand.hpp"
#include <vector>

class OperandFactory {
public:
    typedef IOperand const * (OperandFactory::*member_factory_function_t)(std::string const &) const;
    IOperand const * createOperand( eOperandType type, std::string const & value ) const;
    ~OperandFactory() {};
    OperandFactory() = default;
    OperandFactory(const OperandFactory&) = default;
private:
    OperandFactory& operator=(OperandFactory const&);
    IOperand const * createInt8( std::string const & value ) const;
    IOperand const * createInt16( std::string const & value ) const;
    IOperand const * createInt32( std::string const & value ) const;
    IOperand const * createFloat( std::string const & value ) const;
    IOperand const * createDouble( std::string const & value ) const;
};

const OperandFactory& get_facory();