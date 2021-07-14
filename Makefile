NAME = mimibash

COMPILE = gcc  # -Wall -Wextra -Werror

SRCS = main.c init.c

OBJS =	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): mimibash.h $(OBJS)
	$(COMPILE) $(OBJS) -o $(NAME)

%.o: %.c mimibash.h
	$(COMPILE) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
