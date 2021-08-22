NAME = mimibash

COMPILE = gcc -lreadline -L /Users/$(USER)/.brew/opt/readline/lib -I /Users/$(USER)/.brew/opt/readline/include # -Wall -Wextra -Werror

SRCS = main.c init.c handle_signal.c exec_cmd.c builtins.c print_sorted_env.c arr.c error.c \
		export_unset_utils.c exec_cmd_utils.c split_line.c take_cmd_path.c utils.c update_underscore.c \
		add_back_lst.c get_builtins.c new_split.c parse_redir.c valid_input.c heredoc.c \
		parser.c remove_n.c check_builtins.c pipesplit.c shielding.c shielding_utils.c redir_utils.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

lib:
	cd Libft && make

$(NAME): mimibash.h $(OBJS) lib
	$(COMPILE) -g $(OBJS) Libft/libft.a -o $(NAME)

%.o: %.c mimibash.h
	$(COMPILE) -c -g $< -o $@

clean:
	cd Libft && make clean
	rm -f $(OBJS)

fclean: clean
	cd Libft && make fclean
	rm -f $(NAME)

re: fclean all
