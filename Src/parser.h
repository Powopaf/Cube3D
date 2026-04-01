/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:42:06 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/01 19:18:39 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "gnl.h"

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

int						extract_color(char *tmp, int i);
char					*extract_path_texture(char *tmp, int i);
int						count_line_map(char *tmp, t_map *map);
void					init_data(t_map *map);
int						read_map(t_map *map, char *filename);
int						add_map_line(t_map *map, char *line);
void					add_node_map(t_map *map, char *new_line);
void					convert_map_to_tab_char(t_map *map);
char					*pad_map_line(t_node_map *current, t_map *map);
int						atoi_color(int color, int *i, char *tmp);
int						parse_colors(char *tmp, int *i, t_map *map);
int						parse_texture(char *tmp, int *i, t_map *map);
void					add_node_map(t_map *map, char *new_line);
int						valid_extension(char *filename);

#endif