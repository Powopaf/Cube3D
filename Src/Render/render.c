#include "../../minilibx-linux/mlx.h"
#include <stdlib.h>
#include <math.h>

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
*
* CONST player fov: 60 degrees
* CONST player height: 1 units 
* CONST floor height: 0 units
* CONST ceiling height: 2 units
*/

typedef struct s_cordinate
{
	float x;
	float y;
} t_cordinate;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

#define MAP_WIDTH 5
#define MAP_HEIGHT 5
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 120 // = min(SCREEN_WIDTH / MAP_WIDTH, SCREEN_HEIGHT / MAP_HEIGHT)
#define PI 3.14159265358979323846

static void	pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void draw_vertical_line(t_data *img, int x, int start, int end, int color)
{
	for (int y = start; y < end; y++)
	{
		pixel(img, x, y, color);
	}
}

void draw_horizontal_line(t_data *img, int y, int start, int end, int color)
{
	for (int x = start; x < end; x++)
	{
		pixel(img, x, y, color);
	}
}

float ray_dist(t_cordinate p, float ray_angle, char **map)
{
	
}

void render(t_data *img, char **map, t_cordinate player_pos, float fov)
{
	int i = 0;
	float p_angle = PI / 2; // player facing north
	float ray_angle = p_angle - fov / 2.0f; // start ray angle at the left edge of the player's field of view
	while (i < SCREEN_WIDTH)
	{
		float ray_len = ray_dist(player_pos, ray_angle, map);
		int y_lo = (int)(SCREEN_HEIGHT / 2.0f - 1 / ray_len * SCREEN_HEIGHT / 2.0f); // calculate the top of the wall slice
		int y_hi = (int)(SCREEN_HEIGHT / 2.0f + 1 / ray_len * SCREEN_HEIGHT / 2.0f); // calculate the bottom of the wall slice
		draw_vertical_line(img, i, 0, y_lo - 1, 0xFF0000);
		draw_vertical_line(img, i, y_lo, y_hi, 0x00FF00);
		draw_vertical_line(img, i, y_hi + 1, SCREEN_HEIGHT - 1, 0x0000FF);
		i++;
		ray_angle = p_angle - fov/2 + (i + 0.5) * (fov / SCREEN_WIDTH);
	}
}

int	main()
{
	void	*mlx;
	void	*win;
	float fov = 60;
	t_data img;
	char *map[5] = {
		"11111",
		"11011",
		"10001",
		"10P01",
		"11111"
	};
	t_cordinate player_pos;
	mlx = mlx_init();
	win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "RenderV1");
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	player_pos.x = 300;
	player_pos.y = 420;
	render(&img, map, player_pos, fov);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
