# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pirabaud <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 09:35:24 by pirabaud          #+#    #+#              #
#    Updated: 2022/11/15 09:34:48 by pirabaud         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS  = ft_fill_char_and_increment.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
		ft_isascii.c ft_isprint.c ft_strlen.c ft_strcpy.c ft_strlen_until_c.c \
		ft_strnstr.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_memset.c \
		ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c \
		ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c \
		ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
		ft_strmapi.c ft_striteri.c ft_putchar_fd.c \
		ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	  	ft_putstr.c ft_putchar.c ft_putnbr.c ft_putnbr_base.c \
	  	ft_printf.c ft_printf_utils.c get_next_line.c \
	  	get_next_line_utils.c join_gnl.c ft_strcmp.c	\
	  	ft_dup_dp.c ft_lstadd_front.c ft_lstnew.c ft_lstsize.c \
		ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c \
		ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_print_error.c \
		ft_print_error_utils.c

OBJS	= ${SRCS:.c=.o}

NAME	= libft.a

CC	= clang
RM	= rm -f

CFLAGS	= -Wall -Wextra -Werror

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o} -g

$(NAME):	$(OBJS)
	ar rc  $(NAME) $(OBJS)

all:	$(NAME)

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re:	fclean all

.PHONY:	all clean fclean re
