/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:36:15 by yfarini           #+#    #+#             */
/*   Updated: 2022/10/12 11:07:50 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include <vector>
#include <cinttypes>
#include "Scanner.hpp"
#include "Compiler.hpp"

class VirtualMachine
{
private:
    bool                done;
    Compiler            compiler;
    std::vector<double> stack;
public:
    VirtualMachine(const char*  source);
    void    run();
    ~VirtualMachine();

private:
    bool    check_stack_size(uint32_t size, uint32_t token_index);
};
