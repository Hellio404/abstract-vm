NAME		=	abstract-vm
CC			=	g++
CPPFLAGS    =	-Wall -Wextra -Werror -std=c++17
HEADS		=	Compiler.hpp Exception.hpp IOperand.hpp Operand.hpp OperandFactory.hpp Scanner.hpp Utils.hpp VirtualMachine.hpp
SRCS		=	Compiler.cpp Exception.cpp OperandFactory.cpp Scanner.cpp Utils.cpp VirtualMachine.cpp
OBJS		=	$(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(REGEX) $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) 


clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all