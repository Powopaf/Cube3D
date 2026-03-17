/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:42:06 by sbrochar          #+#    #+#             */
/*   Updated: 2026/03/16 18:37:03 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>

typedef struct s_map

{
	int		map_height;
	int		map_width;
	char	**map;
	int		color_floor;
	int		color_sky;
	int		player_count;
	void	*mlx;
	void	*win;
	int		counter;
	char	*texture_north;
	char	*texture_south;
	char	*texture_east;
	char	*texture_west;
	double	vector_x;
	double	vector_y;
	double	position_player_x;
	double	position_player_y;
	double	vector_camera_shot_x;
	double	vector_camera_shot_y;
	char	player_orientation;

}			t_map;

#endif