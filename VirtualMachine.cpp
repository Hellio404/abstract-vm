/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VirtualMachine.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfarini <yfarini@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:36:19 by yfarini           #+#    #+#             */
/*   Updated: 2023/01/10 17:26:16 by yfarini          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "VirtualMachine.hpp"
#include "Exception.hpp"

VirtualMachine::VirtualMachine(const char *source) : done(false), compiler(source)
{
}

VirtualMachine::~VirtualMachine()
{
}

bool VirtualMachine::check_stack_size(uint32_t size, uint32_t token_index)
{
    if (stack.size() >= size)
        return true;
    throw not_enough_value_in_stack(token_index);
}

#define DO_OPERATION(OP)                               \
    do                                                 \
    {                                                  \
        check_stack_size(2, i);                        \
        const IOperand *rhs = stack[stack.size() - 1]; \
        stack.pop_back();                              \
        const IOperand *lhs = stack[stack.size() - 1]; \
        stack.pop_back();                              \
        stack.push_back(*lhs OP *rhs);                 \
    } while (0)

void VirtualMachine::run()
{
    if (done)
        return;

    done = true;
    try {
        compiler.compile();
    } catch (Compiler::compiler_error &err) {
        std::cerr << err.what() << " errors generated" << std::endl; 
        return ;
    }
        
    std::vector<uint8_t> &instructions = compiler.get_instructions();

    size_t i;
    try
    {
        for (i = 0; i < instructions.size(); ++i)
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
            case OP_OR:
                DO_OPERATION(|);
                break;
            case OP_XOR:
                DO_OPERATION(^);
                break;
            case OP_AND:
                DO_OPERATION(&);
                break;
            case OP_MOD:
                DO_OPERATION(%);
                break;
            case OP_EXIT:
                std::cout << "EXIT" << std::endl;
                return;
            case OP_PRINT:
                check_stack_size(1, i);
                if (stack[stack.size() - 1]->getType() != Int8)
                    throw invalid_type(i);
                std::cout << (char)std::stoi(stack[stack.size() - 1]->toString());
                break;
            case OP_PUSH_i8:
            case OP_PUSH_i16:
            case OP_PUSH_i32:
            case OP_PUSH_f32:
            case OP_PUSH_f64:
            {
                uint16_t offset = (instructions[i + 2] << 8) | instructions[i + 1];
                eOperandType type = (eOperandType)(instructions[i] - OP_PUSH_i8);
                const IOperand *value = get_facory().createOperand(type, (char *)&instructions[offset]);
                this->stack.push_back(value);
                i += 2;
            }
            break;
            case OP_POP:
                if (check_stack_size(1, i) == false)
                    return;
                this->stack.pop_back();
                break;
            case OP_ASSERT:
            {
                if (check_stack_size(2, i) == false)
                    return;
                const IOperand *value = stack[stack.size() - 1];
                const IOperand *asserted_val = stack[stack.size() - 2];
                if (value->getType() != asserted_val->getType() || value->toString() != asserted_val->toString())
                    throw assert_failed(i);
                stack.pop_back();
                break;
            }
            case OP_DUMP:
            {
                auto it = stack.rbegin();
                while (it != stack.rend())
                {
                    std::cout <<(**it).toString()<< std::endl;
                    ++it;
                }
                break;
            }
            default:
                throw invalid_instruction(i);
                break;
            }
        }
    }
    catch (std::overflow_error const &)
    {
        Compiler::raise_error(
            "overflow of an operation",
            &compiler.get_instruction_token()[i]);
    }
    catch (std::underflow_error const &)
    {
        Compiler::raise_error(
            "underflow of an operation",
            &compiler.get_instruction_token()[i]);
    }
    catch (divide_by_zero const &)
    {
        Compiler::raise_error(
            "Dividing by zero is not allowed",
            &compiler.get_instruction_token()[i]);
    }
    catch (virtual_machine_exception &err)
    {
        size_t token_index = err.get_token_index();
        if (token_index == -1)
            token_index = i;
        Compiler::raise_error(
            err.what(),
            &compiler.get_instruction_token()[token_index]
        );
    }
    
}

#undef DO_OPERATION

#include <string>
#include <fstream>
#include <streambuf>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        std::cerr << "Usage: " << argv[0] << " [file]" << std::endl;
        return 1;
    }

    std::string str;
    if (argc < 2)
    {
        // read from stdin until a line found that contains only ";;"
        std::string line;
        while (std::getline(std::cin, line))
        {
            if (line == ";;")
                break;
            str += line + "\n";
        }
    }
    else if (argc == 2)
    {

        std::ifstream t(argv[1]);
        if (!t.is_open())
        {
            std::cerr << "Cannot open file " << argv[1] << std::endl;
            return 1;
        }
        str = std::string((std::istreambuf_iterator<char>(t)),
                          std::istreambuf_iterator<char>());
    }
    VirtualMachine vm(str.c_str());
    vm.run();

}