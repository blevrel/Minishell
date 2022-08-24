# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blevrel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 09:35:57 by blevrel           #+#    #+#              #
#    Updated: 2022/08/24 17:48:49 by blevrel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	srcs/main.c \
		srcs/command.c \
		srcs/redirection.c \
		srcs/signal_handling.c \
		srcs/check.c \
		srcs/check_path.c \
		srcs/minishell_utils.c \
		srcs/modify_quotes.c \
		srcs/parsing_arg.c \
		srcs/check_parsing.c \
		srcs/parsing_quotes.c \
		srcs/cmd_tab_with_quotes.c \

OBJS = ${SRCS:.c=.o}

CC = cc

LIB = -L libft -lft

CFLAGS = -Wall -Wextra -Werror -g

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
	${CC} ${CFLAGS} ${READLINE} ${OBJS} ${HEAD} ${READLINE} ${LIB} -o ${NAME} 

.PHONY: bonus re clean fclean
