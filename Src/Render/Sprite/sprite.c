#include "Render/Sprite/sprite.h"
#include "Render/casting.h"

static int clamp(double w, int size)
{
	return (min(max(w, 0), size - 1));
}

void	draw_sprite(t_p p, int pos[2], double w_x, int face, double y_lh[2])
{
	double	w_y;
	int		i;
	int		offset;
	int		color;

	w_x = clamp(w_x, p.sprite[face].width);
	i = 0;
	while (i < (int)(y_lh[1] - y_lh[0]))
	{
		w_y = (p.sprite[face].height / (y_lh[1] - y_lh[0] + 1.0)) * (pos[1] - y_lh[0]);
		w_y = clamp(w_y, p.sprite[face].height);
		offset = w_y * p.sprite[face].line_length + w_x * (p.sprite[face].bpp / 8);
		color = *(unsigned int *)(p.sprite[face].texture + offset);
		pixel(p.data_struct, pos[0], pos[1] + i, color);
		i++;
	}
}