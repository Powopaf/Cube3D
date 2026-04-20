CC = cc
CFLAGS = -I. -IInclude -Wall -Wextra -Werror -g
NAME = cub3D
LIBS = -L./minilibx-linux -lmlx -lXext -lX11 -lm -lbsd

SRC = Src/Parser/extract_path.c \
	  Src/Parser/read_map.c \
	  Src/Parser/valid_element.c \
	  Src/Parser/valid_map.c \
	  Src/Parser/utils_extract.c \
	  Src/Parser/add_map.c \
	  Src/Parser/parsing.c \
	  Src/GNL/get_next_line_utils.c \
	  Src/GNL/get_next_line.c \
	  Src/Render/casting.c \
	  Src/Render/min_max.c \
	  Src/Render/ray.c \
	  Src/Error/error.c \
	  Src/Game/game.c \
	  Src/Game/key.c \
	  Src/Window/exit_window.c \
	  main.c

OBJ = $(addprefix .obj/,$(SRC:.c=.o))
DEP = $(addprefix .obj/,$(SRC:.c=.d))
MLX = ./minilibx-linux/libmlx.a

all: $(MLX) $(NAME)

$(MLX):
	make -C ./minilibx-linux

$(NAME): $(MLX) $(OBJ)
	$(CC) -o $(NAME) $+ $(LIBS)

.obj/%.o: %.c
	@mkdir -p $(dir $@) .obj
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP)

clean:
	rm -rf .obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re