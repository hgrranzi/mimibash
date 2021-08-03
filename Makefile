NAME = mimibash

COMPILE = gcc -lreadline # -Wall -Wextra -Werror

SRCS = main.c init.c handle_signal.c exec_cmd.c builtins.c arr.c error.c \
		exec_cmd_utils.c split_line.c take_cmd_path.c utils.c \
		add_back_lst.c get_builtins.c new_split.c parse_redir.c \
		parser.c remove_n.c check_builtins.c pipesplit.c shielding.c shielding_utils.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

lib:
	cd Libft && make

$(NAME): mimibash.h builtins.h $(OBJS) lib
	$(COMPILE) -g $(OBJS) Libft/libft.a -o $(NAME)

%.o: %.c mimibash.h builtins.h
	$(COMPILE) -c -g $< -o $@

clean:
	cd Libft && make clean
	rm -f $(OBJS)

fclean: clean
	cd Libft && make fclean
	rm -f $(NAME)

re: fclean all
