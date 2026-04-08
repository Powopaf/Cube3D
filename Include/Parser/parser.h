/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:42:06 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/07 15:44:27 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "struct.h"

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
int						check_walls(char **map_coordinates, t_map *map);
int						scan_map_elements(char **map_coordinates, t_map *map);
void					store_map_info(char c, t_map *map, int x, int y);

#endif