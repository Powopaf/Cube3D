/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:31:38 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/09 11:57:08 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/gnl.h"
#include "Parser/parser.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void	init_data(t_map *map)
{
	map->counter = 0;
	map->color_floor = -1;
	map->color_sky = -1;
	map->player_count = 0;
	map->texture_north = NULL;
	map->texture_south = NULL;
	map->texture_west = NULL;
	map->texture_east = NULL;
	map->node_map = NULL;
	map->map_width = 0;
	map->map_height = 0;
}

int	read_map(t_map *map, char *filename)
{
	char	*line;
	int		fd;

	fd = open(filename, O_RDONLY);
	init_data(map);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (map->counter < 6)
		{
			if (count_line_map(line, map) == 1)
				return (free(line), close(fd), 1);
			free(line);
		}
		else if (map->counter == 6)
		{
			if (add_map_line(map, line) == 1)
				return (free(line), close(fd), 1);
			free(line);
		}
		line = get_next_line(fd);
	}
	convert_map_to_tab_char(map);
	close(fd);
	return (0);
}

void	convert_map_to_tab_char(t_map *map)
{
	int			i;
	t_node_map	*current;

	current = map->node_map;
	i = 0;
	map->map = malloc((sizeof(char *)) * (map->map_height + 1));
	if (!map->map)
		return ;
	while (current != NULL && i < map->map_height)
	{
		map->map[i] = pad_map_line(current, map);
		current = current->next;
		i++;
	}
	map->map[i] = NULL;
	free_all_node(map);
}

char	*pad_map_line(t_node_map *current, t_map *map)
{
	char	*padded_line;
	int		i;

	i = 0;
	padded_line = malloc(sizeof(char) * (map->map_width + 1));
	if (!padded_line)
		return (NULL);
	while (current->read_line[i] != '\0')
	{
		padded_line[i] = current->read_line[i];
		i++;
	}
	while (i < map->map_width)
	{
		padded_line[i] = ' ';
		i++;
	}
	padded_line[i] = '\0';
	return (padded_line);
}
