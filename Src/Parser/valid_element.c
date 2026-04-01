/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:53:35 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/01 15:28:46 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"
#include <unistd.h>

void	store_map_info(char c, t_map *map, int x, int y)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
	{
		map->player_orientation = c;
		map->position_player_x = x;
		map->position_player_y = y;
		map->player_count++;
	}
}

int	scan_map_elements(char **map_coordinates, t_map *map)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (map_coordinates[y][x])
		{
			c = map_coordinates[y][x];
			if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'W'
				&& c != ' ' && c != 'E' && c != '\n' && c != '\r')
			{
				write(2, "Parsing error.\n", 16);
				return (1);
			}
			store_map_info(c, map, x, y);
			x++;
		}
		y++;
	}
	return (0);
}
