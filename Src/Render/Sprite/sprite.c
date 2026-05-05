#include "Render/Sprite/sprite.h"
#include "Render/casting.h"
#include <math.h>

static int clamp(double w, int size)
{
	return (min(max(w, 0), size - 1));
}

static int	get_w_x(t_p map, double pos[2], int face)
{
	double	w_x;
	int		res;
	
	if (face < 2)
	{
		w_x = fmod(pos[0], (double)map.tile_size) / (double)map.tile_size;
		if (w_x < 0.0)
			w_x += 1.0;
		res = (int)(w_x * (double)map.sprite[face].width);
	}
	else
	{
		w_x = fmod(pos[1], (double)map.tile_size) / (double)map.tile_size;
		if (w_x < 0.0)
			w_x += 1.0;
		res = (int)(w_x * (double)map.sprite[face].width);
	}
	return (clamp(res, map.sprite[face].width));
}

void	draw_sprite(t_p p, double pos[2], int face[2], double y_lh[2])
{
	double	w_y;
	int		i;
	int		offset;
	int		color;
	int		w_x;

	w_x = get_w_x(p, pos, face[0]);
	y_lh[0] = max(0, (int)y_lh[0]);
	y_lh[1] = min(SCREEN_HEIGHT - 1, (int)y_lh[1]);
	if (y_lh[0] > y_lh[1])
		return ;
	i = (int)y_lh[0];
	while (i <= (int)y_lh[1])
	{
		w_y = (int)(((i - (int)y_lh[0]) * p.sprite[face[0]].height)
			/ (double)(((int)y_lh[1] - (int)y_lh[0]) + 1));
		w_y = clamp(w_y, p.sprite[face[0]].height);
		offset = w_y * p.sprite[face[0]].line_length + w_x * (p.sprite[face[0]].bpp / 8);
		color = *(unsigned int *)(p.sprite[face[0]].texture + offset);
		pixel(p.data_struct, face[1], i, color);
		i++;
	}
}