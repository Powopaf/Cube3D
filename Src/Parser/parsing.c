/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:05:15 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/14 15:28:56 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	free_all_map(t_map *map)
{
	int	i;

	i = 0;
	if (map->map != NULL)
	{
		while (map->map[i] != NULL)
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
	}
	if (map->texture_north != NULL)
		free(map->texture_north);
	if (map->texture_south != NULL)
		free(map->texture_south);
	if (map->texture_west != NULL)
		free(map->texture_west);
	if (map->texture_east != NULL)
		free(map->texture_east);
	if (map->node_map != NULL)
		free_all_node(map);
}

void	free_all_node(t_map *map)
{
	t_node_map	*current;
	t_node_map	*tmp;

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

void	init_for_parsing(t_map *map)
{
	map->map = NULL;
	map->texture_east = NULL;
	map->texture_north = NULL;
	map->texture_south = NULL;
	map->texture_west = NULL;
	map->player_count = 0;
}

int	parsing(t_map *map, char **av, int ac)
{
	int	i;

	init_for_parsing(map);
	if (ac != 2)
		return ((write(2, "Error: Wrong argument number\n", 29)), 1);
	if (valid_extension(av[1]) == 1)
		return ((write(2, "Error: Bad extension\n", 21)), 1);
	if (read_map(map, av[1]) == 1)
		return ((write(2, "Error: Map reading problem\n", 27)),
			free_all_map(map), 1);
	i = 0;
	if (scan_map_elements(map->map, map) == 1)
		return ((write(2, "Error: Bad element in map\n", 26)),
			free_all_map(map), 1);
	if (check_walls(map->map, map) == 1)
		return ((write(2, "Error: Problem with the walls\n", 30)),
			free_all_map(map), 1);
	free_all_map(map);
	return (0);
}
