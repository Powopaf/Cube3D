#include "../../minilibx-linux/mlx.h"
#include <stdlib.h>

/*
* map:
* 1 1 1 1 1
* 1 1 0 1 1
* 1 0 0 0 1
* 1 0 P 0 1
* 1 1 1 1 1
* P = player
* 1 = wall
* 0 = empty space
* Player face north
* player position: (x:2, y:3)
*/

typedef struct s_cordinate
{
	int x;
	int y;
} t_cordinate;

#define MAP_WIDTH 5
#define MAP_HEIGHT 5

int	main()
{
	void	*mlx;
	void	*win;
	int		sizex;
	int		sizey;
	int fov = 110; // field of view in degrees
	char *map[5] = {
		"11111",
		"11011",
		"10001",
		"10P01",
		"11111"
	};
	t_cordinate player_pos;
	
	player_pos.x = 2;
	player_pos.y = 3;
	mlx = mlx_init();
	mlx_get_screen_size(mlx, &sizex, &sizey); // get screen size
	win = mlx_new_window(mlx, sizex / 2, sizey / 2, "RenderV1");
	mlx_loop(mlx);
}


