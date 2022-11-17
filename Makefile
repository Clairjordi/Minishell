# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clorcery <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/23 14:05:06 by clorcery          #+#    #+#              #
#    Updated: 2022/11/17 16:37:50 by mcloarec         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# /* ~~~~~~~ Colors ~~~~~~~ */
GREEN:="\033[1;32m"
YELLOW:="\033[1;33m"
EOC:="\033[0;0m"
# /* ~~~~~~~~~~~~~~ */

SRCS = mandatory/main.c \
	   mandatory/init/init.c \
	   mandatory/init/init_bis.c \
	   mandatory/free/free.c \
	   mandatory/free/free_bis.c \
	   mandatory/free/free_exit.c \
	   mandatory/signals/signals.c \
	   mandatory/builtins/env.c \
	   mandatory/builtins/export.c \
	   mandatory/builtins/export_utils.c \
	   mandatory/builtins/getexport.c \
	   mandatory/builtins/getexport_utils.c \
	   mandatory/builtins/add_var.c \
	   mandatory/builtins/modify_var.c \
	   mandatory/builtins/exit.c \
	   mandatory/builtins/getenv.c \
	   mandatory/builtins/pwd.c \
	   mandatory/builtins/echo.c \
	   mandatory/builtins/unset.c \
	   mandatory/builtins/cd.c \
	   mandatory/utils/utils.c \
	   mandatory/utils/utils_bis.c \
	   mandatory/utils/create_lst_cmds.c \
	   mandatory/utils/split_pipes.c \
	   mandatory/utils/split_value.c \
	   mandatory/utils/realloc.c \
	   mandatory/parsing/parsing.c \
	   mandatory/parsing/quotes.c \
	   mandatory/parsing/pipes.c \
	   mandatory/parsing/list.c \
	   mandatory/parsing/redirect.c \
	   mandatory/parsing/replace.c \
	   mandatory/parsing/replace_utils.c \
	   mandatory/parsing/dollar.c \
	   mandatory/parsing/dollar_utils.c \
	   mandatory/execute/minishell.c \
	   mandatory/execute/path.c \
	   mandatory/execute/path_utils.c \
	   mandatory/execute/heredoc.c \
	   mandatory/execute/heredoc_utils.c \
	   mandatory/execute/check_sort.c \
	   mandatory/execute/child.c \
	   mandatory/execute/cmd.c \
	   mandatory/execute/sort.c \
	   mandatory/execute/sort_utils.c \
	   mandatory/execute/sort_utils_bis.c \
	   mandatory/execute/builtins.c \
	   mandatory/execute/builtins_bis.c \
	   mandatory/execute/builtins_utils.c \

OBJS = ${SRCS:.c=.o}

NAME = minishell

LIBFT = ./libft/libft.a

FLAGS = -Wall -Wextra -Werror -g

INC = -lreadline 

RM = rm -rf

all: ${NAME}

.c.o:
	@clang ${FLAGS} -c $< -o $@

${LIBFT}:
		@make -C ./libft --no-print-directory

${NAME}: ${OBJS} ${LIBFT}
		@clang ${FLAGS} ${OBJS} ${INC} ${LIBFT} -o ${NAME} 		
		@echo ${GREEN}"compilation complete"${EOC}

clean:
	@make -C ./libft/ clean --no-print-directory
	@${RM} ${OBJS}
	@echo ${YELLOW}"clean ok"${EOC}

run:
	./$(NAME)
run2:
	valgrind ./$(NAME)

fclean: clean
	@${RM} ${LIBFT}
	@${RM} ${NAME}
	@echo ${YELLOW}"fclean ok"${EOC}

re: fclean all

.PHONY: all clean fclean re
