NAME = tester
CC = c++
FLAGS = -Wall -Werror -Wextra -Iincludes -g -O0
SRC = main.cpp vector.cpp map.cpp pair.cpp stack.cpp
SRCS = $(addprefix sources/, $(SRC))
OBJS = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

$(OBJS): $(SRCS)
	$(CC) $(FLAGS) $(SRCS) -c

std: std_objs
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

std_objs:
	$(CC) $(FLAGS) -D STD $(SRCS) -c


clean:
	rm -f $(OBJS)

fclean: clean
	rm -rf $(NAME) exec .vscode *.tmp

re: fclean 
	make $(NAME)

.PHONY: all, clean, fclean, re, std