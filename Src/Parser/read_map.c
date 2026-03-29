/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:31:38 by sbrochar          #+#    #+#             */
/*   Updated: 2026/03/27 17:55:38 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl.h"
#include "parser.h"

void	add_map_line(t_map *map, char *line)
{
	int			len;
	char		*new_line;
	t_node_map	*new_node;
	t_node_map	*current;

	if (!line)
		return ;
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (len == 0)
	{
		free(line);
		return ;
	}
	new_line = ft_substr(line, 0, len);
	if (map->map_width < len)
		map->map_width = len;
	map->map_height++;
	free(line);
	new_node = malloc(sizeof(t_node_map));
	if (!new_node)
	{
		free(new_line);
		return ;
	}
	new_node->read_line = new_line;
	new_node->next = NULL;
	if (map->node_map == NULL)
		map->node_map = new_node;
	else
	{
		current = map->node_map;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

void	read_map(t_map *map, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	map->counter = 0;
	map->color_floor = -1;
	map->color_sky = -1;
	map->node_map = NULL;
	map->map_width = 0;
	map->map_height = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (map->counter < 6)
		{
			count_line_map(line, map);
			free(line);
		}
		else if (map->counter == 6)
			add_map_line(map, line);
		line = get_next_line(fd);
	}
	close(fd);
}
