/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 12:47:38 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 17:07:47 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <string>
#include <cmath>
#include <type_traits>
#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include "Exception.hpp"

template <typename T>
class Operand : public IOperand
{

    std::string str_value;
    const eOperandType type;
    Operand& operator=(Operand const&) ;
public:
    typedef typename OperandTypeTrait<T>::compute_type calculation_type;
    static constexpr typename OperandTypeTrait<T>::converter_type converter = OperandTypeTrait<T>::converter;

    Operand() = delete;
    Operand(const Operand &o):str_value(o.str_value), type(o.type) {};
    ~Operand() {}
    Operand(std::string const &val) : str_value(val), type(OperandTypeTrait<T>::value)
    {
        if (type != Float && type != Double)
        {
            const calculation_type max_vals[] = {
                [Int8] = std::numeric_limits<int8_t>::max(),
                [Int16] = std::numeric_limits<int16_t>::max(),
                [Int32] = std::numeric_limits<int32_t>::max(),
            };

            const calculation_type min_vals[] = {
                [Int8] = std::numeric_limits<int8_t>::min(),
                [Int16] = std::numeric_limits<int16_t>::min(),
                [Int32] = std::numeric_limits<int32_t>::min(),
            };

            calculation_type min_result = min_vals[type];
            calculation_type max_result = max_vals[type];

            calculation_type value = converter(val);

            if (value > max_result)
                throw std::overflow_error("overflow");
            else if (value < min_result)
                throw std::underflow_error("underflow");
        }
    };

    int getPrecision(void) const
    {
        return static_cast<int>(this->type);
    }

    eOperandType getType(void) const
    {
        return this->type;
    }

    eOperandType get_heigher_rank_type(eOperandType type1, eOperandType type2) const
    {
        return static_cast<int>(type1) > static_cast<int>(type2) ? type1 : type2;
    }

    IOperand const *operator+(IOperand const &rhs) const
    {
        eOperandType high = get_heigher_rank_type(this->getType(), rhs.getType());
        IOperand const *result;
        if (high >= Float)
        {
            double lhs_val = custom_stod(this->toString());
            double rhs_val = custom_stod(rhs.toString());
            result = get_facory().createOperand(high, std::to_string(lhs_val + rhs_val));
        }
        else
        {
            long long lhs_val = custom_stoll(this->toString());
            long long rhs_val = custom_stoll(rhs.toString());
            result = get_facory().createOperand(high, std::to_string(lhs_val + rhs_val));
        }
        return result;
    }

    IOperand const *operator-(IOperand const &rhs) const
    {
        eOperandType high = get_heigher_rank_type(this->getType(), rhs.getType());
        IOperand const *result;
        if (high >= Float)
        {
            double lhs_val = custom_stod(this->toString());
            double rhs_val = custom_stod(rhs.toString());
            result = get_facory().createOperand(high, std::to_string(lhs_val - rhs_val));
        }
        else
        {
            long long lhs_val = custom_stoll(this->toString());
            long long rhs_val = custom_stoll(rhs.toString());
            result = get_facory().createOperand(high, std::to_string(lhs_val - rhs_val));
        }

        return result;
    }

    IOperand const *operator*(IOperand const &rhs) const
    {
        eOperandType high = get_heigher_rank_type(this->getType(), rhs.getType());
        IOperand const *result;
        if (high >= Float)
        {
            double lhs_val = custom_stod(this->toString());
            double rhs_val = custom_stod(rhs.toString());
            result = get_facory().createOperand(high, std::to_string(lhs_val * rhs_val));
        }
        else
        {
            long long lhs_val = custom_stoll(this->toString());
            long long rhs_val = custom_stoll(rhs.toString());
            result = get_facory().createOperand(high, std::to_string(lhs_val * rhs_val));
        }
        return result;
    }

    IOperand const *operator/(IOperand const &rhs) const
    {
        eOperandType high = get_heigher_rank_type(this->getType(), rhs.getType());
        IOperand const *result;
        if (high >= Float)
        {
            double lhs_val = custom_stod(this->toString());
            double rhs_val = custom_stod(rhs.toString());
            if (rhs_val == 0)
                throw divide_by_zero();
            result = get_facory().createOperand(high, std::to_string(lhs_val / rhs_val));
        }
        else
        {
            long long lhs_val = custom_stoll(this->toString());
            long long rhs_val = custom_stoll(rhs.toString());
            if (rhs_val == 0)
                throw divide_by_zero();
            result = get_facory().createOperand(high, std::to_string(lhs_val / rhs_val));
        }
        return result;
    }

    IOperand const *operator%(IOperand const &rhs) const
    {
        eOperandType high = get_heigher_rank_type(this->getType(), rhs.getType());
        IOperand const *result;
        if (high >= Float)
        {
            double lhs_val = custom_stod(this->toString());
            double rhs_val = custom_stod(rhs.toString());
            if (rhs_val == 0)
                throw divide_by_zero();
            result = get_facory().createOperand(high, std::to_string(this->modulo(lhs_val, rhs_val)));
        }
        else
        {
            long long lhs_val = custom_stoll(this->toString());
            long long rhs_val = custom_stoll(rhs.toString());
            if (rhs_val == 0)
                throw divide_by_zero();
            result = get_facory().createOperand(high, std::to_string(this->modulo(lhs_val, rhs_val)));
        }
        return result;
    }

    IOperand const *operator|(IOperand const &rhs) const
    {
        eOperandType high = get_heigher_rank_type(this->getType(), rhs.getType());
        IOperand const *result;
        if (high >= Float)
            throw invalid_instruction(-1);
        else
        {
            long long lhs_val = custom_stoll(this->toString());
            long long rhs_val = custom_stoll(rhs.toString());
            result = get_facory().createOperand(high, std::to_string(lhs_val | rhs_val));
        }
        return result;
    }

    IOperand const *operator&(IOperand const &rhs) const
    {
        eOperandType high = get_heigher_rank_type(this->getType(), rhs.getType());
        IOperand const *result;
        if (high >= Float)
            throw invalid_instruction(-1);
        else
        {
            long long lhs_val = custom_stoll(this->toString());
            long long rhs_val = custom_stoll(rhs.toString());
            result = get_facory().createOperand(high, std::to_string(lhs_val & rhs_val));
        }
        return result;
    }

    IOperand const *operator^(IOperand const &rhs) const
    {
        eOperandType high = get_heigher_rank_type(this->getType(), rhs.getType());
        IOperand const *result;
        if (high >= Float)
            throw invalid_instruction(-1);
        else
        {
            long long lhs_val = custom_stoll(this->toString());
            long long rhs_val = custom_stoll(rhs.toString());
            result = get_facory().createOperand(high, std::to_string(lhs_val ^ rhs_val));
        }
        return result;
    }

    std::string const &toString(void) const
    {
        return this->str_value;
    }

private:
    long long modulo(long long a, long long b) const
    {
        return a % b;
    }

    double modulo(double a, double b) const
    {
        return std::fmod(a, b);
    }
};
