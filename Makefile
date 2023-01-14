NAME		=	abstract_vm
CXX			=	g++
CPPFLAGS    =	-Wall -Wextra -Werror -std=c++17
HEADS		=	Compiler.hpp Exception.hpp IOperand.hpp Operand.hpp OperandFactory.hpp Scanner.hpp Utils.hpp VirtualMachine.hpp
SRCS		=	Compiler.cpp Exception.cpp OperandFactory.cpp Scanner.cpp Utils.cpp VirtualMachine.cpp abstract_vm.cpp
OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(REGEX) $(OBJS)
	$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS) 


clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all