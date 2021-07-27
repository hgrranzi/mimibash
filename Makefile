NAME = mimibash

COMPILE = gcc -lreadline # -Wall -Wextra -Werror

SRCS = main.c init.c handle_signal.c exec_cmd.c builtins.c arr.c error.c \
		exec_cmd_utils.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): mimibash.h builtins.h $(OBJS)
	$(COMPILE) $(OBJS) -o $(NAME)

%.o: %.c mimibash.h builtins.h
	$(COMPILE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
