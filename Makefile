# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blevrel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 09:35:57 by blevrel           #+#    #+#              #
#    Updated: 2022/08/18 10:22:18 by pirabaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	srcs/main.c \
		srcs/command.c \
		srcs/redirection.c \
		

OBJS = ${SRCS:.c=.o}

CC = cc

LIB = -L libft -lft

CFLAGS = -Wall -Wextra -Werror

HEAD = -I includes -I libft

READLINE = -lreadline

RM = rm -f

all: ${NAME}

clean:
	make clean -sC libft
	${RM} ${OBJS}

fclean: clean
	make fclean -sC libft
	${RM} ${NAME}

re: fclean all

.c.o:
	${CC} ${CFLAGS} -c ${HEAD} ${READLINE} $< -o ${<:.c=.o}

${NAME}:${OBJS}
	make -sC libft
	${CC} ${CFLAGS} ${READLINE} ${OBJS} ${HEAD} ${READLINE} ${LIB} -o ${NAME} -g

.PHONY: bonus re clean fclean
