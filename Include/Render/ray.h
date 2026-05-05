/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 13:46:46 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/20 14:49:47 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include "struct.h"

# define STEP 0.045
# define PI 3.14159265358979323846

/* 
* FOV = PI / 3
*/

# define FOV 1.0471975511965976

typedef enum e_face
{
	FACE_UNKNOWN,
	FACE_NORTH = 0,
	FACE_SOUTH = 1,
	FACE_EAST = 2,
	FACE_WEST = 3
}					t_face;

typedef struct s_wall
{
	t_face				face;
	int					wall_x;
	int					wall_y;
}						t_wall;

double	ray_dist(t_p p, double ray_angle, t_map map, t_wall *wall);

#endif
