# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blevrel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 09:35:57 by blevrel           #+#    #+#              #
#    Updated: 2022/09/08 12:18:21 by blevrel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	srcs/command.c \
		srcs/builtin.c \
		srcs/minishell_utils.c \
		srcs/redirection.c \
		srcs/parsing_with_space.c \
		srcs/check.c \
		srcs/check_quotes.c \
		srcs/dup_pipe.c \
		srcs/tokenizing.c \
		srcs/get_env_variable.c \
		srcs/tokenized_quotes_size.c \
		srcs/fill_tokenized_cmd.c \
		srcs/pipe.c	\
		srcs/check_parsing.c \
		srcs/fill_cmd.c \
		srcs/parsing_arg.c \
		srcs/check_path.c \
		srcs/init_struct_pipe.c \
		srcs/parsing_with_quotes.c \
		srcs/signal_handling.c \
		srcs/parsing_with_redirection.c \
		srcs/main.c \

OBJS = ${SRCS:.c=.o}

CC = gcc

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
