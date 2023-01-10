/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:47:46 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 16:26:02 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"
#include "Operand.hpp"


OperandFactory& OperandFactory::operator=(const OperandFactory&) 
{
    return *this;
}

IOperand const * OperandFactory::createOperand( eOperandType type, std::string const & value ) const {
    member_factory_function_t mb_methods[] {
        &OperandFactory::createInt8,
        &OperandFactory::createInt16,
        &OperandFactory::createInt32,
        &OperandFactory::createFloat,
        &OperandFactory::createDouble
    };
    return (this->*mb_methods[type])(value);
}

IOperand const * OperandFactory::createInt8( std::string const & value ) const {
    return new Operand<int8_t>(value);
}

IOperand const * OperandFactory::createInt16( std::string const & value ) const {
    return new Operand<int16_t>(value);
}

IOperand const * OperandFactory::createInt32( std::string const & value ) const {
    return new Operand<int32_t>(value);
}

IOperand const * OperandFactory::createFloat( std::string const & value ) const {
    return new Operand<float>(value);
}

IOperand const * OperandFactory::createDouble( std::string const & value ) const {
    return new Operand<double>(value);
}

const OperandFactory& get_facory() {
    static const OperandFactory factory;
    return factory;
}
