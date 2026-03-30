/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 12:31:38 by sbrochar          #+#    #+#             */
/*   Updated: 2026/03/30 17:25:40 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl.h"
#include "../parser.h"

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
	convert_map_to_tab_char(map);
	close(fd);
}

void	convert_map_to_tab_char(t_map *map)
{
	int			i;
	t_node_map	*current;
	t_node_map	*tmp;

	current = map->node_map;
	i = 0;
	map->map = malloc((sizeof(char *)) * (map->map_height + 1));
	if (!map->map)
		return ;
	while (current != NULL)
	{
		map->map[i] = pad_map_line(current, map);
		current = current->next;
		i++;
	}
	map->map[i] = NULL;
	current = map->node_map;
	while (current != NULL)
	{
		free(current->read_line);
		tmp = current->next;
		free(current);
		current = tmp;
	}
	map->node_map = NULL;
}

char	*pad_map_line(t_node_map *current, t_map *map)
{
	char	*padded_line;
	int		i;

	i = 0;
	padded_line = malloc(sizeof(char) * map->map_width + 1);
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
