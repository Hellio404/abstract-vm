/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:47:38 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 17:12:28 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <type_traits>
#include "Utils.hpp"
enum eOperandType {
    Int8,
    Int16,
    Int32,
    Float,
    Double
};

/// map each type int8_t, int_16_t... to its proper 
/// - eOperandType representation, 
/// - type to hold it when doing computations
/// - function to use to convert it from string
template <typename T>
struct OperandTypeTrait {};

template <>
struct OperandTypeTrait<int8_t> { 
    typedef long long           compute_type;;
    typedef compute_type (*converter_type)(std::string const&);
    static const eOperandType   value = Int8;
    static constexpr converter_type converter = &custom_stoll;
};

template <>
struct OperandTypeTrait<int16_t> { 
    typedef long long           compute_type;
    typedef compute_type (*converter_type)(std::string const&);
    static const eOperandType   value = Int16;
    static constexpr converter_type converter = &custom_stoll;
};

template <>
struct OperandTypeTrait<int32_t> { 
    typedef long long           compute_type;
    typedef compute_type (*converter_type)(std::string const&);
    static const eOperandType   value = Int32;
    static constexpr converter_type converter = &custom_stoll;
};

template <>
struct OperandTypeTrait<float> { 
    typedef double           compute_type;
    typedef compute_type (*converter_type)(std::string const&);
    static const eOperandType   value = Float;
    static constexpr converter_type converter = &custom_stod;
};

template <>
struct OperandTypeTrait<double> {
    typedef double           compute_type;
    typedef compute_type (*converter_type)(std::string const&);
    static const eOperandType   value = Double;
    static constexpr converter_type converter = &custom_stod;
};


class IOperand {
public:
    virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
    virtual eOperandType getType( void ) const = 0; // Type of the instance
    virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
    virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
    virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
    virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
    virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
    virtual IOperand const * operator|( IOperand const & rhs ) const = 0; // Modulo
    virtual IOperand const * operator^( IOperand const & rhs ) const = 0; // Modulo
    virtual IOperand const * operator&( IOperand const & rhs ) const = 0; // Modulo
    virtual std::string const & toString( void ) const = 0; // String representation of the instance
    virtual ~IOperand( void ) {}

    virtual eOperandType get_heigher_rank_type(eOperandType type1, eOperandType type2) const = 0;

};
