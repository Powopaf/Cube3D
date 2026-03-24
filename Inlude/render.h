/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 10:56:20 by pifourni          #+#    #+#             */
/*   Updated: 2026/03/24 12:40:04 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

#include "mlx_struct.h"
#include "struct.h"

/*
* TILE_SIZE = min(SCREEN_WIDTH / MAP_WIDTH, SCREEN_HEIGHT / MAP_HEIGHT)
*/
#define TILE_SIZE 120
#define PI 3.14159265358979323846
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define FOV PI / 3.0

enum Face
{
	FACE_UNKNOWN,
	FACE_NORTH,
	FACE_SOUTH,
	FACE_EAST,
	FACE_WEST
};

void render(t_data *img, char **map, t_player p);

#endif
