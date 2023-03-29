# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: colas <colas@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/26 15:04:30 by mfinette          #+#    #+#              #
#    Updated: 2023/03/29 10:19:52 by colas            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC		= cc
FLAGS	= -fsanitize=address -g3 -Wall -Wextra -Werror
AR		= ar rcs
RM		= @rm -f
HEADER	= msh.h
DEF_COLOR = \033[0;39m
YELLOW = \033[0;93m
GREEN = \033[0;92m
BLUE = \033[0;94m
CYAN = \033[0;96m

FILES = main							\
		builtins/builtins				\
		builtins/env					\
		builtins/env2					\
		builtins/expand					\
		builtins/export					\
		builtins/export2				\
		builtins/unset					\
		builtins/dvd					\
		parsing/parsing_hub				\
		parsing/dollar					\
		parsing/get_cmd_nbr				\
		parsing/get_redir				\
		parsing/quotes_dollars_and_redir\
		parsing/quotes_utils_and_replace_spaces				\
		parsing/get_and_check_fd		\
		utils/parse_utils				\
		utils/msh_utils					\
		utils/cmd_utils					\
		utils/env_utils					\
		utils/ft_split					\
		utils/ft_calloc					\
		utils/itoa						\
		commands/cmds					\
		commands/paths					\
		ft_err_printf/ft_print_hexa		\
		ft_err_printf/ft_printf			\
		ft_err_printf/ft_putnbr			\
		ft_err_printf/ft_putnbr_u		\
		ft_err_printf/ft_putstr_int		\
		history							\
		free_things						\
		error							\
		signal							

all: $(NAME)

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

%.o:%.c $(HEADER)
	@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
	@$(CC) $(FLAGS) -c $< -o $@ 

$(NAME): $(OBJS)
	@echo "$(GREEN)😳😎minishell compiled!😎😳$(DEF_COLOR)"
	@${CC} ${FLAGS} ${SRCS} -o ${NAME} -l readline
	./minishell

clean:
	@$(RM) $(OBJS)
	@echo "$(CYAN)minishell object files cleaned!$(DEF_COLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(CYAN)3$(DEF_COLOR)"
	@sleep 0.2
	@echo "$(CYAN)2$(DEF_COLOR)"
	@sleep 0.2
	@echo "$(CYAN)1$(DEF_COLOR)"
	@sleep 0.2
	@echo "$(GREEN)minishell executable files cleaned!$(DEF_COLOR)"


re: fclean all

.PHONY: all clean fclean re