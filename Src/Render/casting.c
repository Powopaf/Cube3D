/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:13:58 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/14 13:37:29 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "Render/ray_casting.h"
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

static void	draw(t_data *img, double dist[3], t_face wallface, t_map map)
{
	int	y_lo;
	int	y_hi;
	int	color;

	y_lo = (int)(((double)SCREEN_HEIGHT / 2.0) - (map.tile_size / dist[0])
			* dist[1]);
	y_hi = (int)(((double)SCREEN_HEIGHT / 2.0) + (map.tile_size / dist[0])
			* dist[1]);
	color = 0xFFFFFF;
	if (wallface == FACE_NORTH)
		color = 0xFF0000;
	else if (wallface == FACE_SOUTH)
		color = 0x00FF00;
	else if (wallface == FACE_EAST)
		color = 0x0000FF;
	else if (wallface == FACE_WEST)
		color = 0xFFFF00;
	else
		color = 0xFFFFFF;
	draw_vertical_line(img, (int)dist[2], (int [2]){0, y_lo - 1}, 0xFF000F);
	draw_vertical_line(img, (int)dist[2],
		(int [2]){MAX(0, y_lo), MIN(SCREEN_HEIGHT - 1, y_hi)}, color);
	draw_vertical_line(img, (int)dist[2],
		(int [2]){y_hi + 1, SCREEN_HEIGHT - 1}, 0xD000FF);
}

void	render(t_data *img, t_map map, t_p p)
{
	int		i;
	t_face	wall_face;
	double	ray_angle;
	double	projdist;
	double	perpdist;

	i = 0;
	while (i < SCREEN_WIDTH)
	{
		ray_angle = p.angle + atan(c_x(i) * tan(FOV / 2.0));
		projdist = (SCREEN_WIDTH / 2.0) / tan(FOV / 2.0);
		perpdist = ray_dist(p, ray_angle, map.map, &wall_face);
		if (perpdist < 0.0001)
			perpdist = 0.0001;
		draw(img, (double [3]){perpdist, projdist, (double)i}, wall_face, map);
		i++;
	}
}
