NAME = mimibash

READLINE_LIB = -lreadline -L ~/.brew/opt/readline/lib

READLINE_INCLUDE = -I ~/.brew/opt/readline/include

COMPILE = gcc #-Wall -Wextra -Werror

LIB_DIR = Libft/libft.a

SRCS = main.c mimibash.c init.c handle_signal.c exec_cmd.c builtins.c builtins_again.c print_sorted_env.c arr.c wildcard.c \
		export_unset_utils.c exec_cmd_utils.c exec_cmd_finish.c split_line.c take_cmd_path.c utils.c update_underscore.c \
		add_back_lst.c get_builtins.c new_split.c parse_redir.c valid_input.c heredoc.c check_fd.c dollar_parser.c\
		parser.c remove_n.c check_builtins.c pipesplit.c shielding.c shielding_utils.c redir_utils.c parse_star.c check_builtins_utils.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): mimibash.h $(OBJS)
	$(MAKE) -C $(dir $(LIB_DIR))
	$(COMPILE) $(READLINE_LIB) -g $(OBJS) $(LIB_DIR) -o $(NAME)

%.o: %.c mimibash.h
	$(COMPILE) -c -g $< -o $@ $(READLINE_INCLUDE)

clean:
	cd Libft && make clean
	rm -f $(OBJS)

fclean: clean
	cd Libft && make fclean
	rm -f $(NAME)

re: fclean all
