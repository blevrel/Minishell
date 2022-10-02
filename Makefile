# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blevrel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 09:35:57 by blevrel           #+#    #+#              #
#    Updated: 2022/09/30 16:45:38 by blevrel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	srcs/add_space_to_cmd.c \
		srcs/ch_directory.c \
		srcs/check_builtin.c \
		srcs/check.c \
		srcs/check_parsing.c \
		srcs/check_path.c \
		srcs/check_quotes.c \
		srcs/check_space_before_index.c \
		srcs/command.c \
		srcs/dup_pipe.c \
		srcs/echo.c \
		srcs/env.c \
		srcs/env_parsing_utils.c \
		srcs/exit.c \
		srcs/export_utils.c \
		srcs/fill_arg.c \
		srcs/fill_tokenized_cmd.c \
		srcs/free.c \
		srcs/ft_strstr_index.c \
		srcs/get_cmd_tab_size.c \
		srcs/get_env_variable.c \
		srcs/here_doc.c \
		srcs/init_null.c\
		srcs/init_struct_pipe.c \
		srcs/init_struct_pipe_utils.c \
		srcs/main.c \
		srcs/minishell_utils.c \
		srcs/new_export.c \
		srcs/new_export_env.c \
		srcs/parsing_arg.c \
		srcs/parsing_with_quotes.c \
		srcs/parsing_with_redirection.c \
		srcs/parsing_with_space_and_env_var.c \
		srcs/pipe.c	\
		srcs/pwd.c \
		srcs/signal_handling.c \
		srcs/tokenized_quotes_size.c \
		srcs/tokenizing.c \
		srcs/unset.c \

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
