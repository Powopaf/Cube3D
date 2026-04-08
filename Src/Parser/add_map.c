/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:13:17 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/01 19:17:48 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/gnl.h"
#include "Parser/parser.h"
#include <stdlib.h>
#include <unistd.h>

void	add_node_map(t_map *map, char *new_line)
{
	t_node_map	*new_node;
	t_node_map	*current;

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

int	add_map_line(t_map *map, char *line)
{
	int		len;
	char	*new_line;

	if (!line)
		return (1);
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (len == 0)
	{
		free(line);
		if (map->map_height > 0)
			return (1);
		return (0);
	}
	new_line = ft_substr(line, 0, len);
	if (map->map_width < len)
		map->map_width = len;
	map->map_height++;
	free(line);
	add_node_map(map, new_line);
	return (0);
}
