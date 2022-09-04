# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clorcery <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 10:51:59 by clorcery          #+#    #+#              #
#    Updated: 2022/07/19 10:31:54 by clorcery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~~ Colors ~~~~~~~ */
BLACK:="\033[1;30m"
RED:="\033[1;31m"
GREEN:="\033[1;32m"
YELLOW:="\033[1;33m"
BLUE:="\033[1;34m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
WHITE:="\033[1;37m"
EOC:="\033[0;0m"
# /* ~~~~~~~~~~~~~~ */

SRCS	= libft/ft_isalpha.c \
			libft/ft_isdigit.c \
			libft/ft_isalnum.c \
			libft/ft_isascii.c \
			libft/ft_isprint.c \
			libft/ft_strlen.c \
			libft/ft_memset.c \
			libft/ft_bzero.c \
			libft/ft_memcpy.c \
			libft/ft_memmove.c \
			libft/ft_strlcpy.c \
			libft/ft_strlcat.c \
			libft/ft_toupper.c \
			libft/ft_tolower.c \
			libft/ft_strchr.c \
			libft/ft_strrchr.c \
			libft/ft_strncmp.c \
			libft/ft_strcmp.c \
			libft/ft_memchr.c \
			libft/ft_memcmp.c \
			libft/ft_strnstr.c \
			libft/ft_atoi.c \
			libft/ft_atoll.c \
			libft/ft_strdup.c \
			libft/ft_calloc.c \
			libft/ft_substr.c \
			libft/ft_strjoin.c \
			libft/ft_strtrim.c \
			libft/ft_split.c \
			libft/ft_itoa.c \
			libft/ft_strmapi.c \
			libft/ft_striteri.c \
			libft/ft_putchar_fd.c \
			libft/ft_putchar.c \
			libft/ft_putstr_fd.c \
			libft/ft_putstr.c \
			libft/ft_putendl_fd.c \
			libft/ft_putnbr_fd.c \
			libft/ft_putnbr_base.c \
			libft/ft_error.c \
			libft/ft_lstnew.c \
			libft/ft_lstadd_front.c \
			libft/ft_lstsize.c \
			libft/ft_lstlast.c \
			libft/ft_lstadd_back.c \
			libft/ft_lstdelone.c \
			libft/ft_lstclear.c \
			libft/ft_lstiter.c \
			libft/ft_dlstnew.c \
			libft/ft_dlstadd_back.c \
			libft/ft_dlstadd_front.c \
			libft/ft_dlstlast.c \
			libft/ft_lstmap.c \
			libft/ft_max_int.c \
			libft/ft_min_int.c \
			libft/ft_next_int.c \
			libft/ft_prev_int.c \
			libft/ft_free_tab_char.c \
			libft/ft_swap.c \
			printf/ft_printf.c \
			printf/ft_printf_utils.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c 

DIR_SRCS = ./srcs/

OBJS 	= ${SRCS:.c=.o}

DIR_OBJS = ./objs/

#~~~~~~~~ mettre les .o dans le dossier OBJS~~~~~~~~~#

#SRC = $(addprefix ${DIR_SRCS}, ${SRCS})
OBJ = $(addprefix ${DIR_OBJS}, ${OBJS}) 

#~~~~~~~~~~~~~~~~~~~~~~~#

NAME	= libft.a

MKDIR = mkdir -p

RM	= rm -rf

CC	= gcc

CLIB	= ar

CFLAGS	= -Wall -Wextra -Werror

LFLAGS	= rcs

${DIR_OBJS}%.o: ${DIR_SRCS}%.c
	@${MKDIR} ${dir $@}
	@${CC} ${CFLAGS} -c  $< -o $@

${NAME}:	${OBJ}
		@${CLIB} ${LFLAGS} ${NAME} ${OBJ}
		@echo ${GREEN}"compilation libft complete"${EOC}

all:		${NAME}

clean:
	@if [ -d ${DIR_OBJS} ]; then \
		${RM} ${DIR_OBJS}; \
	fi

fclean:		clean
		@if [ -f ${NAME} ]; then \
			${RM} ${NAME}; \
		fi

re:		fclean all 

.PHONY:		all clean fclean re
