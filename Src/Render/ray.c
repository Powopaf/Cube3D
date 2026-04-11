/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:28:06 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/10 12:28:09 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Render/game.h"
#include "struct.h"
#include <math.h>

static double	move_ray(double *info[4], int map_xy[2], t_map map, t_p p)
{
	double	dist_x;
	double	dist_y;

	*info[2] += *info[0] * STEP;
	*info[3] += *info[1] * STEP;
	map_xy[0] = (int)(*info[2] / (double)map.tile_size);
	map_xy[1] = (int)(*info[3] / (double)map.tile_size);
	if (map_xy[0] < 0 || map_xy[0] >= map.map_width
		|| map_xy[1] < 0 || map_xy[1] >= map.map_height)
		return (INFINITY);
	else if (map.map[map_xy[1]][map_xy[0]] == '1')
	{
		dist_x = *info[2] - p.x;
		dist_y = *info[3] - p.y;
		return (sqrt(dist_x * dist_x + dist_y * dist_y));
	}
	return (-1);
}

/*
* info[0] = dir_x
* info[1] = dir_y
* info[2] = ray_x
* info[3] = ray_y
*/

static void	find_face(e_face *face, int map_xy[2], double info[4], int prev[2])
{
	if (map_xy[0] != prev[0])
	{
		if (info[0] > 0.0)
			*face = FACE_WEST;
		else
			*face = FACE_EAST;
	}
	else if (map_xy[1] != prev[1])
	{
		if (info[1] > 0.0)
			*face = FACE_NORTH;
		else
			*face = FACE_SOUTH;
	}
}

double	ray_dist(t_p p, double ray_angle, t_map map, int *face)
{
	double	info[4];
	int		map_xy[2];
	int		prev_map_x;
	int		prev_map_y;
	double	dist;

	*face = FACE_UNKNOWN;
	info[0] = cos(ray_angle);
	info[1] = sin(ray_angle);
	info[2] = p.x;
	info[3] = p.y;
	prev_map_x = (int)(info[2] / (double)map.tile_size);
	prev_map_y = (int)(info[3] / (double)map.tile_size);
	while (1)
	{
		dist = move_ray(info, map_xy, map, p);
		if (dist >= 0)
		{
			find_face(face, map_xy, info, (int [2]){prev_map_x, prev_map_y});
			return (dist);
		}
		prev_map_x = map_xy[0];
		prev_map_y = map_xy[1];
	}
	return (INFINITY);
}
