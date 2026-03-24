CC = cc
CFLAGS =  -Wall -Wextra -Werror -MMD -MP -g -fsanitize=address
NAME = cub3D
LIBS = -fsanitize=address

SRC = main.c

OBJ = $(addprefix .obj/,$(SRC:.c=.o))
DEP = $(addprefix .obj/,$(SRC:.c=.d))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $+ $(LIBS)

.obj/%.o: %.c
	@mkdir -p .obj
	$(CC) $(CFLAGS) -I. -IIinclude -c $< -o $@

-include $(DEP)

clean:
	rm -rf .obj

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
