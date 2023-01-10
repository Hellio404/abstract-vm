/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:36:15 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 16:24:57 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <cinttypes>
#include "Scanner.hpp"
#include "Compiler.hpp"
#include "IOperand.hpp"
#include "OperandFactory.hpp"

class VirtualMachine
{
private:
    bool                            done;
    Compiler                        compiler;
    std::vector<const IOperand*>    stack;
    VirtualMachine& operator=(VirtualMachine const&);
public:
    VirtualMachine() = delete;
    VirtualMachine(const char*  source);
    VirtualMachine(const VirtualMachine&) = default;
    void    run();
    ~VirtualMachine();

private:
    bool    check_stack_size(uint32_t size, uint32_t token_index);
};
