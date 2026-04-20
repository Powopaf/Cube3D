/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:46:46 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/14 14:05:01 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "struct.h"

# define STEP 0.01
# define PI 3.14159265358979323846

static const double	g_fov = PI / 3.0;

typedef enum e_face
{
	FACE_UNKNOWN,
	FACE_NORTH,
	FACE_SOUTH,
	FACE_EAST,
	FACE_WEST
}	t_face;

double	ray_dist(t_p p, double ray_angle, char **map, t_face *face);

#endif
