/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:36:19 by yfarini           #+#    #+#             */
/*   Updated: 2022/10/13 11:31:00 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VirtualMachine.hpp"


VirtualMachine::VirtualMachine(const char *source): done(false), compiler(source)
{
}

VirtualMachine::~VirtualMachine()
{
}

bool    VirtualMachine::check_stack_size(uint32_t size, uint32_t token_index)
{
    if (stack.size() >= size)
        return true;
    Compiler::raise_error(
        "stack doesn't contains enough value for operation",
        &compiler.get_instruction_token()[token_index]
    );
    return false;
}


void    VirtualMachine::run()
{
    #define DO_OPERATION(OP) \
    do { \
        if (check_stack_size(2, i) == false)\
            return ;\
        double rhs = stack[stack.size() - 1];\
        stack.pop_back();\
        double lhs = stack[stack.size() - 1];\
        stack.pop_back();\
        stack.push_back(lhs OP rhs);\
    } while (0)\

    if (done) return ;

    done = true;
    if (compiler.compile() == false)
        return ;
    
    std::vector<uint8_t>&   instructions = compiler.get_instructions();
    for (int i = 0; i < instructions.size(); ++i)
    {
        switch (instructions[i])
        {
        case OP_ADD:
            DO_OPERATION(+);
            break;
        case OP_SUB:
            DO_OPERATION(-);
            break;
        case OP_MUL:
            DO_OPERATION(*);
            break;
        case OP_DIV:
            DO_OPERATION(/);
            break;
        case OP_EXIT:
            std::cout << "EXIT" << std::endl;
            return ;
        case OP_PRINT:
            if (check_stack_size(1, i) == false)
                return ;
            std::cout << stack[stack.size() - 1] << std::endl;
            break;
        case OP_PUSH_f64:
        {
            uint16_t offset = (instructions[i + 2] << 8 ) | instructions[i + 1];
            i += 2;
            stack.push_back(atof((char *)&instructions[offset]));
        }
        break;
        default:
            std::cout << "UNKOWNK INSTRUCTION" << std::endl;
            break;
        }
    }
    #undef DO_OPERATION
}
#include <string>
#include <fstream>
#include <streambuf>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: ./vm script" << std::endl;
        return 1;
    }
    std::ifstream t(argv[1]);
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    
    VirtualMachine vm(str.c_str());

    vm.run();
    
}