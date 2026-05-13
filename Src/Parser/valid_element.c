/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:53:35 by sbrochar          #+#    #+#             */
/*   Updated: 2026/05/12 16:00:53 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/gnl.h"
#include "Parser/parser.h"
#include <string.h>
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
				return (write(2, "Error: One element in map is incorrect\n",
						39), 1);
			store_map_info(c, map, x, y);
			if (c == 'N' || c == 'W' || c == 'E' || c == 'S')
				map_coordinates[y][x] = '0';
			x++;
		}
		y++;
	}
	if (map->player_count != 1)
		return (write(2, "Error: Incorrect number of players\n", 35), 1);
	return (0);
}

static int	check_walls_utils(char **map_coordinates, t_map *map, int x, int y)
{
	if (y == 0 || y == map->map_height - 1 || x == 0 || !map_coordinates[y][x
		+ 1])
		return (write(2, "Error: Map border open\n", 23), 1);
	if (x >= (int)ft_strlen(map_coordinates[y - 1]) || map_coordinates[y
			- 1][x] == ' ' || map_coordinates[y - 1][x] == '\n'
		|| x >= (int)ft_strlen(map_coordinates[y + 1]) || map_coordinates[y
		+ 1][x] == ' ' || map_coordinates[y + 1][x] == '\n'
		|| map_coordinates[y][x - 1] == ' ' || map_coordinates[y][x + 1] == ' '
		|| map_coordinates[y][x + 1] == '\n')
		return (write(2, "Error: Map leak detected\n", 25), 1);
	return (0);
}

int	check_walls(char **map_coordinates, t_map *map)
{
	int	x;
	int	y;
	int	status;

	status = 0;
	y = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (map_coordinates[y][x])
		{
			if (map_coordinates[y][x] == '0')
			{
				status = check_walls_utils(map_coordinates, map, x, y);
				if (status == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
