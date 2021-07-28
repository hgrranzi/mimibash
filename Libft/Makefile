# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tmiranda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/24 15:24:07 by tmiranda          #+#    #+#              #
#    Updated: 2020/11/24 18:03:24 by tmiranda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= ft_memset.c \
		  ft_bzero.c \
		  ft_memcpy.c \
		  ft_memccpy.c \
		  ft_memmove.c \
		  ft_memchr.c \
		  ft_memcmp.c \
		  ft_strlen.c \
		  ft_strlcpy.c \
		  ft_strlcat.c \
		  ft_strchr.c \
		  ft_strrchr.c \
		  ft_strnstr.c \
		  ft_strncmp.c \
		  ft_atoi.c \
		  ft_isalpha.c \
		  ft_isdigit.c \
		  ft_isalnum.c \
		  ft_isascii.c \
		  ft_isprint.c \
		  ft_toupper.c \
		  ft_tolower.c \
		  ft_calloc.c \
		  ft_strdup.c \
		  ft_substr.c \
		  ft_strjoin.c \
		  ft_strtrim.c \
		  ft_split.c \
		  ft_itoa.c \
		  ft_strmapi.c \
		  ft_putchar_fd.c \
		  ft_putstr_fd.c \
		  ft_putendl_fd.c \
		  ft_putnbr_fd.c \
		  ft_lstnew.c \
		  ft_lstadd_front.c \
		  ft_lstsize.c \
		  ft_lstlast.c \
		  ft_lstadd_back.c \
		  ft_lstdelone.c \
		  ft_lstclear.c \
		  ft_lstiter.c 

OBJSB	= ${BONUS:.c=.o}
OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

GCC		= gcc

RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror

%.o : %.c	libft.h 
			${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

#.c.o:		libft.h
#			${GCC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS} # libft.h
			ar rcs ${NAME} ${OBJS}

.PHONY: all
all:		${NAME}	


.PHONY: bonus
bonus:		all ${OBJSB} # libft.h
			ar rcs ${NAME} ${OBJSB}

.PHONY: clean
clean:	
			${RM} ${OBJS}
			${RM} ${OBJSB}
.PHONY: fclean
fclean:		clean
			${RM} ${NAME}
.PHONY: re
re:			fclean all

	
