# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blevrel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 09:35:57 by blevrel           #+#    #+#              #
#    Updated: 2022/10/10 14:03:07 by blevrel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
#Rajouter les fichiers pour l'ajout des espaces dans SRCS
SRCS =	srcs/alloc_parsing.c \
		srcs/ch_directory.c \
		srcs/check_builtin.c \
		srcs/check.c \
		srcs/check_parsing.c \
		srcs/check_path.c \
		srcs/check_quotes.c \
		srcs/command.c \
		srcs/count_arg.c \
		srcs/dup_pipe.c \
		srcs/echo.c \
		srcs/env.c \
		srcs/exit.c \
		srcs/export_utils.c \
		srcs/fill_arr_parse.c \
		srcs/free.c \
		srcs/here_doc.c \
		srcs/init_null.c\
		srcs/init_struct_pipe.c \
		srcs/init_struct_pipe_utils.c \
		srcs/main.c \
		srcs/minishell_utils.c \
		srcs/new_export.c \
		srcs/new_export_env.c \
		srcs/parsing.c \
		srcs/pipe.c	\
		srcs/pwd.c \
		srcs/replace_env.c \
		srcs/signal_handling.c \
		srcs/tokenizing.c \
		srcs/tokenizing_size.c \
		srcs/unset.c \
		srcs/verif_malloc.c \

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
