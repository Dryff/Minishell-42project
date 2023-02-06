NAME		=	pipex
HEADER		=	pipex.h ft_err_printf/ft_printf.h GNL/get_next_line.h

SRCS		= 	pipex.c ft_split.c pipex_utils.c check.c \
				ft_err_printf/ft_putstr_int.c ft_err_printf/ft_printf.c \
				ft_err_printf/ft_print_hexa.c ft_err_printf/ft_putnbr_u.c ft_err_printf/ft_putnbr.c \
				GNL/get_next_line.c GNL/get_next_line_utils.c \
				

OBJS		:= $(SRCS:%.c=%.o)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	print $(OBJS) compile
			@echo "\033[31m > Done!"

compile:	
			@gcc -o $(NAME) ft_split.o pipex.o pipex_utils.o check.o ft_err_printf/ft_print_hexa.o ft_err_printf/ft_putnbr_u.o ft_err_printf/ft_putnbr.o ft_err_printf/ft_putstr_int.o ft_err_printf/ft_printf.o 

$(OBJS): %.o:%.c ${HEADER} Makefile
			@echo "\033[36m compiling: $<"
			@$(CC) $(CFLAGS) -c $< -o $@

print:		
			@echo "\033[31m ~ Compiling pipex ~"

clean:
	@echo "\033[31m > Removed all objects files <"
	@rm -rf *.o ft_err_printf/*.o GNL/*.o

fclean: clean
	@echo "\033[31m * Removed $(HEADER) *"	
	@rm -rf $(NAME)

re: fclean all

.PHONY:		all clean fclean re