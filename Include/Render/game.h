#ifndef GAME_H
# define GAME_H

#include "struct.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PI 3.14159265358979323846
#define FOV (PI / 3.0)
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

typedef struct s_p
{
	double	x;
	double	y;
	double angle;
} t_p;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

int run(t_map *map);

#endif