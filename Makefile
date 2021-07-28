NAME = mimibash

COMPILE = gcc -lreadline # -Wall -Wextra -Werror

SRCS = main.c init.c handle_signal.c exec_cmd.c builtins.c arr.c error.c \
		exec_cmd_utils.c split_line.c take_cmd_path.c utils.c \
		add_back_lst.c get_builtins.c new_split.c parse_redir.c \
		parse_first_arg.c parser.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

lib:
	cd Libft && make

$(NAME): mimibash.h builtins.h $(OBJS) lib
	$(COMPILE) $(OBJS) Libft/libft.a -o $(NAME)

%.o: %.c mimibash.h builtins.h
	$(COMPILE) -c $< -o $@

clean:
	cd Libft && make clean
	rm -f $(OBJS)

fclean: clean
	cd Libft && make fclean
	rm -f $(NAME)

re: fclean all
