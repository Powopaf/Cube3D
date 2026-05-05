/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/20 14:41:21 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/20 14:50:36 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Render/casting.h"
#include "Render/ray.h"
#include "struct.h"
#include "minilibx-linux/mlx.h"
#include "Render/Sprite/sprite.h"
#include <math.h>

static double	c_x(int i)
{
	return (2.0 * ((double)i + 0.5) / (double)SCREEN_WIDTH - 1.0);
}

static void	pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_vertical_line(t_data *img, int x, int y_range[2], int color)
{
	int	start;
	int	end;

	start = y_range[0];
	end = y_range[1];
	while (start <= end)
	{
		pixel(img, x, start, color);
		start++;
	}
}

static void	draw(t_p p, double dist[3], t_wall wall, t_map map)
{
	int	y_lo;
	int	y_hi;
	int	color;

	y_lo = (int)(((double)SCREEN_HEIGHT / 2.0) - (map.tile_size / dist[0])
			* dist[1]);
	y_hi = (int)(((double)SCREEN_HEIGHT / 2.0) + (map.tile_size / dist[0])
			* dist[1]);
	if (dist[0] == INFINITY)
		draw_vertical_line(p.data_struct->img, (int)dist[2], (int [2]){max(0, y_lo),
			min(SCREEN_HEIGHT - 1, y_hi)}, 0xFFFFFF);
	if (wall.face == FACE_NORTH)
		draw_sprite(p, (int)dist[3], (int)dist[4], fmod(dist[3], map.tile_size), wall.face);
	else if (wall.face == FACE_SOUTH)
		draw_sprite(p, (int)dist[3], (int)dist[4], fmod(dist[3], map.tile_size), wall.face);
	else if (wall.face == FACE_EAST)
		draw_sprite(p, (int)dist[3], (int)dist[4], fmod(dist[4], map.tile_size), wall.face);
	else if (wall.face == FACE_WEST)
		draw_sprite(p, (int)dist[3], (int)dist[4], fmod(dist[4], map.tile_size), wall.face);
	else
		draw_vertical_line(p.data_struct->img, (int)dist[2], (int [2]){max(0, y_lo),
			min(SCREEN_HEIGHT - 1, y_hi)}, 0xFFFFFF);
	draw_vertical_line(p.data_struct->img, (int)dist[2], (int [2]){0, y_lo - 1},
		map.color_sky);
	draw_vertical_line(p.data_struct->img, (int)dist[2],
		(int [2]){y_hi + 1, SCREEN_HEIGHT - 1}, map.color_floor);
}

/* info[0] = perpdist
*  info[1] = projdist
*/

int	render(void *param)
{
	t_p		*p;
	int		i;
	t_wall	wall;
	double	ray_angle;
	double	info[2];

	p = (t_p *)param;
	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray_angle = p->angle + atan(c_x(i) * tan(FOV / 2.0));
		info[1] = (SCREEN_WIDTH / 2.0) / tan(FOV / 2.0);
		info[0] = ray_dist(*p, ray_angle, *p->map_struct, &wall)
			* cos(ray_angle - p->angle);
		if (info[0] < 0.0001)
			info[0] = 0.0001;
		draw(*p, (double [3]){info[0], info[1], (double)i}, wall, *p->map_struct);
		i++;
	}
	mlx_put_image_to_window(p->data_struct->mlx, p->data_struct->win,
		p->data_struct->img, 0, 0);
	return (0);
}
