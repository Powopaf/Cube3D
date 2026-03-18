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
	double x;
	double y;
} t_cordinate;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

#define MAP_WIDTH 8
#define MAP_HEIGHT 6
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define TILE_SIZE 120 // = min(SCREEN_WIDTH / MAP_WIDTH, SCREEN_HEIGHT / MAP_HEIGHT)
#define PI 3.14159265358979323846
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define FACE_UNKNOWN -1
#define FACE_NORTH 0
#define FACE_SOUTH 1
#define FACE_EAST 2
#define FACE_WEST 3

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

double ray_dist(t_cordinate p, double ray_angle, char **map, int *face)
{
	const double step = 0.01; // step size for ray marching
	double dir_x = cos(ray_angle);
	double dir_y = sin(ray_angle);
	double ray_x = p.x;
	double ray_y = p.y;
	int prev_map_x = (int)(ray_x / (double)TILE_SIZE);
	int prev_map_y = (int)(ray_y / (double)TILE_SIZE);
	*face = FACE_UNKNOWN;
	while (1)
	{
		ray_x += dir_x * step;
		ray_y += dir_y * step;
		int map_x = (int)(ray_x / (double)TILE_SIZE);
		int map_y = (int)(ray_y / (double)TILE_SIZE);
		if (map_x < 0 || map_x >= MAP_WIDTH || map_y < 0 || map_y >= MAP_HEIGHT)
			return INFINITY; // ray goes out of bounds
		if (map[map_y][map_x] == '1')
		{
			if (map_x != prev_map_x)
			{
				if (dir_x > 0.0)
					*face = FACE_WEST;
				else
					*face = FACE_EAST;
			}
			else if (map_y != prev_map_y)
			{
				if (dir_y > 0.0)
					*face = FACE_NORTH;
				else
					*face = FACE_SOUTH;
			}
			double dist_x = ray_x - p.x;
			double dist_y = ray_y - p.y;
			return sqrt(dist_x * dist_x + dist_y * dist_y); // return the distance from the player to the wall
		}
		prev_map_x = map_x;
		prev_map_y = map_y;
	}
}
/*
* -1 0 1
*    P
*/
void render(t_data *img, char **map, t_cordinate player_pos, double fov)
{
	int i = 0;
	double p_angle = -PI / 2.0 + -30 * PI / 180.0; // keep previous player angle behavior
	while (i < SCREEN_WIDTH)
	{
		int wall_face;
		int wall_color;
		double c_x = 2.0 * (i + 0.5) / (double)SCREEN_WIDTH - 1.0; // calculate the camera plane x coordinate for the current ray
		double ray_angle = p_angle + atan(c_x * tan(fov / 2.0)) ;
		double projdist = (SCREEN_WIDTH / 2.0) / tan(fov / 2.0); // calculate the distance from the player to the projection plane
		double ray_len = ray_dist(player_pos, ray_angle, map, &wall_face); // calculate the distance from the player to the wall for the current ray
		double perpdist = ray_len * cos(ray_angle - p_angle); // correct the distance for the fish-eye effect
		if (perpdist < 0.0001)
			perpdist = 0.001; // prevent division by zero
		int y_lo = (int)(SCREEN_HEIGHT / 2.0 - TILE_SIZE / 2.0 * projdist / perpdist); // calculate the top of the wall slice
		int y_hi = (int)(SCREEN_HEIGHT / 2.0 + TILE_SIZE / 2.0 * projdist / perpdist); // calculate the bottom of the wall slice
		wall_color = 0x00FF00;
		if (wall_face == FACE_WEST)
			wall_color = 0xFFAA00;
		else if (wall_face == FACE_EAST)
			wall_color = 0xFF0000;
		else if (wall_face == FACE_SOUTH)
			wall_color = 0x0000FF;
		else if (wall_face == FACE_NORTH)
			wall_color = 0x00FFFF;
		//draw_vertical_line(img, i, 0, y_lo - 1, 0xFF0000);
		draw_vertical_line(img, i, max(0, y_lo), min(SCREEN_HEIGHT - 1, y_hi), wall_color);
		//draw_vertical_line(img, i, y_hi + 1, SCREEN_HEIGHT - 1, 0x0000FF);
		i++;
	}
}

int	main()
{
	void	*mlx;
	void	*win;
	double fov = 60 * (double)PI / 180.0; // convert fov to radians
	t_data img;
	char *map[6] = {
		"11111111",
		"10000001",
		"10100001",
		"10000001",
		"1000P001",
		"11111111"
	};
	t_cordinate player_pos;
	mlx = mlx_init();
	win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "RenderV1");
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	player_pos.x = 4 * TILE_SIZE + TILE_SIZE / 2.0; // player is in the center of the tile
	player_pos.y = 4 * TILE_SIZE + TILE_SIZE / 2.0; // player is in the center of the tile
	render(&img, map, player_pos, fov);
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_loop(mlx);
}
