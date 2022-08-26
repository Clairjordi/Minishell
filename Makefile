# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clorcery <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 14:05:06 by clorcery          #+#    #+#              #
#    Updated: 2022/08/26 12:55:38 by clorcery         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~~ Colors ~~~~~~~ */
GREEN:="\033[1;32m"
YELLOW:="\033[1;33m"
EOC:="\033[0;0m"
# /* ~~~~~~~~~~~~~~ */

SRCS = Mandatory/main.c

OBJS = ${SRCS:.c=.o}

NAME = minishell

LIBFT = ./Libft/libft.a

FLAGS = -Wall -Wextra -Werror -g

RM = rm -rf

all: ${NAME}

.c.o:
	@gcc ${FLAGS} -c $< -o $@

${LIBFT}:
		@make -C ./Libft --no-print-directory

${NAME}: ${OBJS} ${LIBFT}
		@gcc ${FLAGS} ${OBJS} ${LIBFT} -o ${NAME}		
		@echo ${GREEN}"compilation complete"${EOC}

clean:
	@make -C ./Libft clean --no-print-directory
	@${RM} ${OBJS}
	@echo ${YELLOW}"clean ok"${EOC}

fclean: clean
	@${RM} ${LIBFT}
	@${RM} ${NAME}
	@echo ${YELLOW}"fclean ok"${EOC}

re: fclean all

.PHONY: all clean fclean re
