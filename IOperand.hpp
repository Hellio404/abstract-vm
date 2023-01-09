/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:47:38 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/09 13:04:37 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <type_traits>
enum eOperandType {
    Int8,
    Int16,
    Int32,
    Float,
    Double
};

// map each type int8_t, int_16_t... to it's proper eOperandType representation
template <typename T>
struct OperandTypeTrait {};
template <>
struct OperandTypeTrait<int8_t> { static const eOperandType value = Int8; };
template <>
struct OperandTypeTrait<int16_t> { static const eOperandType value = Int16; };
template <>
struct OperandTypeTrait<int32_t> { static const eOperandType value = Int32; };
template <>
struct OperandTypeTrait<float> { static const eOperandType value = Float; };
template <>
struct OperandTypeTrait<double> { static const eOperandType value = Double; };

class IOperand {
public:
    virtual int getPrecision( void ) const = 0; // Precision of the type of the instance
    virtual eOperandType getType( void ) const = 0; // Type of the instance
    virtual IOperand const * operator+( IOperand const & rhs ) const = 0; // Sum
    virtual IOperand const * operator-( IOperand const & rhs ) const = 0; // Difference
    virtual IOperand const * operator*( IOperand const & rhs ) const = 0; // Product
    virtual IOperand const * operator/( IOperand const & rhs ) const = 0; // Quotient
    virtual IOperand const * operator%( IOperand const & rhs ) const = 0; // Modulo
    virtual std::string const & toString( void ) const = 0; // String representation of the instance
    virtual ~IOperand( void ) {}

    virtual eOperandType get_heigher_rank_type(eOperandType type1, eOperandType type2) const = 0;

};

template <typename T>
class Operand: public IOperand {
    const T                 value;
    const eOperandType      type;
public:
    Operand() = delete;
    Operand(const Operand&) = delete;
    Operand(T const& val): value(val), type(OperandTypeTrait<T>::value) {};
    Operand(std::string const& val): value(val), type(OperandTypeTrait<T>::value) {};
    
    int getPrecision( void ) const {
        return static_cast<int>(this->type);
    }

    eOperandType getType( void ) const {
        return this->type;
    }

    eOperandType get_heigher_rank_type(eOperandType type1, eOperandType type2) const {
        return static_cast<int>(type1) > static_cast<int>(type2) ? type1 : type2;
    }


    IOperand const * operator+( IOperand const & rhs ) const {
        eOperandType high = get_heigher_rank_type(this->getType(), rhs.getType());

        if (high == Float || high == Double) {
            return this->plus_floats(high, rhs);
        } else {
            return this->plus_ints(high, rhs);
        }
    }

    IOperand const * operator-( IOperand const & rhs ) const {
        throw "unimplemented";
    }

    IOperand const * operator*( IOperand const & rhs ) const {
        throw "unimplemented";
    }

    IOperand const * operator/( IOperand const & rhs ) const {
        throw "unimplemented";
    }

    IOperand const * operator%( IOperand const & rhs ) const {
        throw "unimplemented";
    }

    std::string const & toString( void ) const {
        return std::to_string(value);
    }

private:

    IOperand const * plus_floats(eOperandType result_type, IOperand const & rhs ) const {
            double rhs_val = std::stod(rhs.toString());
            IOperand *result = factory::createOperand(result_type, std::to_string(this->value + rhs_val));
            return result;
    }

    IOperand const * plus_ints(eOperandType result_type, IOperand const & rhs ) const {
        const long long max_vals[] = {
            [ Int8 ] = std::numeric_limits<int8_t>::max,
            [ Int16 ] = std::numeric_limits<int16_t>::max,
            [ Int32 ] = std::numeric_limits<int32_t>::max,
        };

        const long long min_vals[] = {
            [ Int8 ] = std::numeric_limits<int8_t>::min,
            [ Int16 ] = std::numeric_limits<int16_t>::min,
            [ Int32 ] = std::numeric_limits<int32_t>::min,
        };
        long long rhs_val = std::stoll(rhs.toString());
        
        long long min_result = min_vals[result_type];
        long long max_result = max_vals[result_type];

        if (this->value > 0 && rhs_val > max_result - this->value)
            throw std::overflow_error("operator+");
        else if (this->value < 0 && rhs_val < min_result -  this->value )
            throw std::underflow_error("operator+");
        
        IOperand *result = factory::createOperand(result_type, std::to_string(this->value + rhs_val));
        return result;
    }
};



