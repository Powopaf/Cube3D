/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 11:36:57 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/14 11:45:41 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_CASTING_H
# define RAY_CASTING_H

# include "struct.h"

# define STEP 0.01
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define PI 3.14159265358979323846
# define FOV (PI / 3.0)
# define MIN(a, b) ((a) < (b) ? (a) : (b))
# define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef enum e_face
{
	FACE_UNKNOWN,
	FACE_NORTH,
	FACE_SOUTH,
	FACE_EAST,
	FACE_WEST
}	t_face;

int		run(t_map *map);
double	ray_dist(t_p p, double ray_angle, char **map, t_face *face);

#endif
