/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:05:15 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/09 13:41:42 by sbrochar         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_map	my_map;
	int		i;

	my_map.map = NULL;
	my_map.texture_east = NULL;
	my_map.texture_north = NULL;
	my_map.texture_south = NULL;
	my_map.texture_west = NULL;
	my_map.player_count = 0;
	if (argc != 2)
	{
		printf("Erreur\nVeuillez fournir une carte (.cub) en argument.\n");
		return (1);
	}
	if (valid_extension(argv[1]) == 1)
		return ((write(2, "Error: Bad extension\n", 21)), 1);
	if (read_map(&my_map, argv[1]) == 1)
	{
		printf("Erreur Parsing: sur read_map\n");
		free_all_map(&my_map);
		return (1);
	}
	printf("NO: %s\n", my_map.texture_north);
	printf("SO: %s\n", my_map.texture_south);
	printf("WE: %s\n", my_map.texture_west);
	printf("EA: %s\n", my_map.texture_east);
	printf("Floor: %d\n", my_map.color_floor);
	printf("Sky: %d\n", my_map.color_sky);
	i = 0;
	if (scan_map_elements(my_map.map, &my_map) == 1)
	{
		printf("Erreur Parsing: sur scan_map_elements\n");
		free_all_map(&my_map);
		return (1);
	}
	printf("Joueur X: %f\n", my_map.position_player_x);
	printf("Joueur Y: %f\n", my_map.position_player_y);
	printf("Orientation: %c\n", my_map.player_orientation);
	i = 0;
	while (my_map.map[i] != NULL)
	{
		printf("%s\n", my_map.map[i]);
		i++;
	}
	if (check_walls(my_map.map, &my_map) == 1)
	{
		printf("Erreur Parsing: sur check_walls\n");
		free_all_map(&my_map);
		return (1);
	}
	printf("SUCCES ABSOLU: CARTE VALIDE ET ETANCHE\n");
	free_all_map(&my_map);
	return (0);
}
