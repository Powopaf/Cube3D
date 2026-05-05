#include "Render/Sprite/sprite.h"
#include "Render/casting.h"

static int clamp(double w, int size)
{
	return (min(max(w, 0), size - 1));
}

void	draw_sprite(t_p p, int x, int y, double w_x, int face)
{
	double	w_y;
}