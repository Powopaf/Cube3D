/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:53:35 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/09 11:21:47 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser/parser.h"
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
				return (write(2, "Error: Bad element\n", 19), 1);
			store_map_info(c, map, x, y);
			if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
				map_coordinates[y][x] = '0';
			x++;
		}
		y++;
	}
	if (map->player_count != 1)
		return (1);
	return (0);
}

int	check_walls(char **map_coordinates, t_map *map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (map_coordinates[y][x])
		{
			if (map_coordinates[y][x] == '0')
			{
				if (y == 0 || y == map->map_height - 1 || x == 0
					|| x == map->map_width - 1)
					return (write(2, "Error: Hole in the map\n", 23), 1);
				if (map_coordinates[y - 1][x] == ' ' || map_coordinates[y
					+ 1][x] == ' ' || map_coordinates[y][x - 1] == ' '
					|| map_coordinates[y][x + 1] == ' ')
					return (write(2, "Error: Hole in the map\n", 23), 1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
