INCLUDES	+= fractol fl_complex fl_fractols
INCLUDES	+= fl_hooks
INCLUDES	:= $(addprefix src/, $(INCLUDES))
INCLUDES	:= $(addsuffix .o, $(INCLUDES))
CC			:= gcc
FLAGS		+= -Wall -Wextra -Werror -Ilibft/include/ -Iinclude/ -Imlx
FLAGS		+= -g -Ofast
FRAME		:= -framework OpenGL -framework Appkit
NAME		:= fractol

.PHONY: clean fclean re all

all: $(NAME)

$(NAME): $(INCLUDES) libft/libftprintf.a mlx/libmlx.a
	@echo 'Building $(NAME)'
	@$(CC) $(FLAGS) $(FRAME) $^ -o $@

%.o: %.c
	@$(CC) $(FLAGS) -c $^ -o $@

libft/libftprintf.a:
	@make -C libft/

mlx/libmlx.a:
	@make -C mlx/

rclean:
	@make -C libft/ fclean
	@make -C mlx/ clean

clean:
	@echo 'Removing $(NAME)--object files'
	@rm -rf $(INCLUDES)

fclean: clean
	@echo 'Removing $(NAME)'
	@rm -rf $(NAME)

re: fclean all
