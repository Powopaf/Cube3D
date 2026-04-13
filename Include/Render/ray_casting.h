#ifndef GAME_H
# define GAME_H

#include "struct.h"

#define STEP 0.01
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

typedef enum e_face
{
	FACE_UNKNOWN,
	FACE_NORTH,
	FACE_SOUTH,
	FACE_EAST,
	FACE_WEST
} e_face;

int run(t_map *map);
double	ray_dist(t_p p, double ray_angle, char **map, e_face *face);

#endif