/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:42:06 by sbrochar          #+#    #+#             */
/*   Updated: 2026/03/27 17:44:32 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "gnl.h"
# include <stdbool.h>
# include <string.h>
#include <stdlib.h>


typedef struct s_node_map
{
	char				*read_line;
	struct s_node_map	*next;
}						t_node_map;
typedef struct s_map

{
	int					map_height;
	int					map_width;
	char				**map;
	t_node_map			*node_map;
	int					color_floor;
	int					color_sky;
	int					player_count;
	void				*mlx;
	void				*win;
	int					counter;
	char				*texture_north;
	char				*texture_south;
	char				*texture_east;
	char				*texture_west;
	double				vector_x;
	double				vector_y;
	double				position_player_x;
	double				position_player_y;
	double				vector_camera_shot_x;
	double				vector_camera_shot_y;
	char				player_orientation;

}						t_map;

int	extract_color(char *tmp, int i);
char	*extract_path_texture(char *tmp, int i);
void	count_line_map(char *tmp, t_map *map);
void	read_map(t_map *map, char *filename);

#endif