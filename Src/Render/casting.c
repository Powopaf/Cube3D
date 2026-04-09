#include "struct.h"
#include "Render/game.h"
#include <math.h>

static double c_x(int i)
{
	return (2.0 * (i + 0.5) / (double)SCREEN_WIDTH - 1.0);
}

static double ray_dist(t_p p, double ray_angle, char **map, e_face *face)
{

}

void render(t_data *img, t_map map, t_p p)
{
	int	i;
	e_face wall_face;
	double ray_angle;
	double projdist;
	double perpdist;
	int y_lo;
	int y_hi;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray_angle = p.angle + atan(c_x(i) * tan(FOV / 2.0));
		projdist = (SCREEN_WIDTH / 2.0) / tan(FOV / 2.0);
		perpdist = ray_dist(p, ray_angle, map.map, &wall_face);
		if (perpdist < 0.0001)
			perpdist = 0.0001;
		y_lo = (int)((double)SCREEN_HEIGHT / 2.0 - (double)SCREEN_HEIGHT / (2.0 * perpdist));
		y_hi = (int)((double)SCREEN_HEIGHT / 2.0 + (double)SCREEN_HEIGHT / (2.0 * perpdist));
		int wall_color = 0x00FF00;
		if (wall_face == FACE_NORTH)
			wall_color = 0xFF0000; //replace by sprite color
		else if (wall_face == FACE_SOUTH)
			wall_color = 0x00FF00; //replace by sprite color
		else if (wall_face == FACE_EAST)
			wall_color = 0x0000FF; // replace by sprite color
		else if (wall_face == FACE_WEST)
			wall_color = 0xFFFF00; // replace by sprite color
		/*
			draw the good pixel color for the wall slice, ceiling and floor
		*/
}