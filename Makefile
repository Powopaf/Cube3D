CC = cc
CFLAGS =  -Wall -Wextra -Werror -g -fsanitize=address
NAME = cub3D
LIBS = -fsanitize=address

SRC = Src/Parser/extract_path.c \
	  Src/Parser/read_map.c \
	  Src/Parser/valid_element.c \
	  Src/Parser/valid_map.c \
	  Src/Parser/utils_extract.c \
	  Src/Parser/add_map.c \
	  Src/Parser/main_test.c \
	  Src/GNL/get_next_line_utils.c \
	  Src/GNL/get_next_line.c \
	  

OBJ = $(addprefix .obj/,$(SRC:.c=.o))
DEP = $(addprefix .obj/,$(SRC:.c=.d))

all: $(NAME)

$(NAME): $(OBJ)
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