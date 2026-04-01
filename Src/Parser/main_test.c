/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 17:05:15 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/01 12:20:45 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

int	main(int argc, char **argv)
{
	t_map	my_map;
	int		i;

	if (argc != 2)
	{
		printf("Erreur\nVeuillez fournir une carte (.cub) en argument.\n");
		return (1);
	}
	if (read_map(&my_map, argv[1]) == 1)
	{
		if (my_map.texture_north != NULL)
			free(my_map.texture_north);
		if (my_map.texture_south != NULL)
			free(my_map.texture_south);
		if (my_map.texture_west != NULL)
			free(my_map.texture_west);
		if (my_map.texture_east != NULL)
			free(my_map.texture_east);
		return (1);
	}
	printf("NO: %s\n", my_map.texture_north);
	printf("SO: %s\n", my_map.texture_south);
	printf("WE: %s\n", my_map.texture_west);
	printf("EA: %s\n", my_map.texture_east);
	printf("Floor: %d\n", my_map.color_floor);
	printf("Sky: %d\n", my_map.color_sky);
	i = 0;
	if (my_map.map != NULL)
	{
		printf("\n=== RESULTAT DU PARSING ===\n\n");
		while (my_map.map[i] != NULL)
		{
			printf("%s\n", my_map.map[i]);
			i++;
		}
		printf("\n===========================\n");
	}
	i = 0;
	if (my_map.map != NULL)
	{
		while (my_map.map[i] != NULL)
		{
			free(my_map.map[i]);
			i++;
		}
		free(my_map.map);
	}
	if (my_map.texture_north != NULL)
		free(my_map.texture_north);
	if (my_map.texture_south != NULL)
		free(my_map.texture_south);
	if (my_map.texture_west != NULL)
		free(my_map.texture_west);
	if (my_map.texture_east != NULL)
		free(my_map.texture_east);
	return (0);
}
