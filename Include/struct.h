/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 13:56:38 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/14 20:11:44 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_node_map
{
	char				*read_line;
	struct s_node_map	*next;
}						t_node_map;

typedef struct s_map
{
	int					map_height;
	int					map_width;
	int					tile_size;
	char				**map;
	t_node_map			*node_map;
	int					color_floor;
	int					color_sky;
	int					player_count;
	int					counter;
	char				*texture_north;
	char				*texture_south;
	char				*texture_east;
	char				*texture_west;
	double				position_player_x;
	double				position_player_y;
	char				player_orientation;

}						t_map;

typedef struct s_data
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	void				*mlx;
	void				*win;
}						t_data;

typedef struct s_p
{
	double				x;
	double				y;
	double				angle;
	int					speed;
	char				**map;
	int					tile_size;
	t_map				*map_struct;
	t_data				*data_struct;
}						t_p;

#endif
