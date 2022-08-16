# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blevrel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 09:35:57 by blevrel           #+#    #+#              #
#    Updated: 2022/08/16 15:02:08 by blevrel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = srcs/command_parsing.c \

OBJS = ${SRCS:.c=.o}

CC = cc

LIB = -L libft -lft

CFLAGS = -Wall -Wextra -Werror

HEAD = -I includes -I libft

READLINE = -lreadline

RM = rm -f

all: ${NAME}

clean:
	make clean -C libft
	${RM} ${OBJS}

fclean: clean
	make fclean -C libft
	${RM} ${NAME}

re: fclean all

.c.o:
	${CC} ${CFLAGS} -c ${HEAD} ${READLINE} $< -o ${<:.c=.o}

${NAME}:${OBJS}
	make -C libft
	${CC} ${CFLAGS} ${READLINE} ${OBJS} ${HEAD} ${READLINE} ${LIB} -o ${NAME} -g

.PHONY: bonus re clean fclean
