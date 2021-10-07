NAME = fdf
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./includes
MLX_INCLUDE =
MLX_DIR=./minilibx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -framework OpenGl -framework AppKit

#source
SRCS_DIR = sources/
SRCS = main.c parse_file.c errors.c mlx_utils.c utils.c\
		draw_segment.c draw.c colors.c map_tools.c palete.c\
		hooks.c\

SRCS_PREFIXED = $(addprefix $(SRCS_DIR), $(SRCS))

#objsm
OBJS = $(SRCS_PREFIXED:.c=.o)

all : $(NAME)

%.o: %.c ./includes/fdf.h ./includes/color.h
	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@
$(NAME): $(OBJS)
	@$(MAKE) re -C ./libft
	@$(MAKE) -C $(MLX_DIR)
	@echo "\033[0;32m libmlx.dylib builded \033[m"
	@$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -lm $(MLX_FLAGS) -o $(NAME)
	@cp $(MLX_DIR)/libmlx.dylib libmlx.dylib
	@echo "\033[0;32m libmlx.dylib copied \033[m"
	@echo $(NAME) est construit

clean :
	@$(MAKE) clean -C ./libft
	@$(MAKE) clean -C $(MLX_DIR)
	@rm -rf $(OBJS)
	@echo cleaning

fclean : clean
	@$(MAKE) fclean -C ./libft
	@rm -rf $(NAME)
	@rm -rf libmlx.dylib
	@echo "full clean"

re : fclean all

map42:all
	./fdf maps/42.map
map_simple:all
	./fdf maps/42.map
help	:
	@echo "all $(NAME) clean fclean re \033[0;32m map42 map_simple help\033[m"

.PHONY	: all clean fclean re help
