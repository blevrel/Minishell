# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: blevrel <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/16 09:35:57 by blevrel           #+#    #+#              #
#    Updated: 2022/11/15 17:02:29 by blevrel          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS  =	srcs/alloc_parsing.c \
		srcs/ch_directory.c \
		srcs/check.c \
		srcs/check_builtin.c \
		srcs/check_echo_options.c \
		srcs/check_echo_options_utils.c \
		srcs/check_parsing.c \
		srcs/check_path.c \
		srcs/check_quotes.c \
		srcs/check_redirection.c \
		srcs/check_space_utils.c \
		srcs/check_syntax_error.c \
		srcs/cmd_arr_with_echo_n.c \
		srcs/command.c \
		srcs/count_arg.c \
		srcs/count_cmd_pipes.c \
		srcs/dup_pipe.c \
		srcs/echo.c \
		srcs/echo_utils.c \
		srcs/env.c \
		srcs/exit.c \
		srcs/export_utils.c \
		srcs/fill_arr_parse.c \
		srcs/free.c \
		srcs/here_doc.c \
		srcs/here_doc_limiter.c \
		srcs/init_null.c\
		srcs/init_struct_pipe.c \
		srcs/init_struct_pipe_utils.c \
		srcs/isolate_env.c \
		srcs/main.c \
		srcs/minishell_utils.c \
		srcs/new_export.c \
		srcs/new_export_env.c \
		srcs/parsing.c \
		srcs/ft_pipe.c	\
		srcs/pipe_utils.c \
		srcs/pwd.c \
		srcs/remove_first_arg.c \
		srcs/replace_env.c \
		srcs/reset_index.c \
		srcs/signal_handling.c \
		srcs/tokenize_full_arg_with_quotes.c \
		srcs/tokenize_here_doc_line.c \
		srcs/tokenizing.c \
		srcs/tokenizing_size.c \
		srcs/unset.c \
		srcs/verif_malloc.c \
		srcs/print_export.c \
		srcs/return_value.c \
		srcs/parsing_heredoc.c \
		srcs/parsing_export.c \
		srcs/parsing_returnvalue.c \
		srcs/move_index.c \
		srcs/parsing_export_utils.c \
		srcs/count_size_arg.c \
		srcs/init_file.c \
		srcs/fill_new_export.c \

OBJS = ${SRCS:.c=.o}

CC = clang

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
	${CC} ${CFLAGS} -c ${HEAD} $< -o ${<:.c=.o}

${NAME}:${OBJS}
	make -sC libft
	${CC} ${CFLAGS} ${OBJS} ${HEAD} ${READLINE} ${LIB} -o ${NAME} 

.PHONY: bonus re clean fclean
