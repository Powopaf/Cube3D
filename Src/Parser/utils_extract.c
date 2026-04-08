/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:01:44 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/01 18:42:35 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/gnl.h"
#include "Parser/parser.h"
#include <unistd.h>

int	atoi_color(int color, int *i, char *tmp)
{
	while (tmp[*i] >= '0' && tmp[*i] <= '9')
	{
		color = (color * 10) + (tmp[*i] - '0');
		(*i)++;
	}
	return (color);
}

int	parse_texture(char *tmp, int *i, t_map *map)
{
	if ((tmp[*i] == 'N' && tmp[*i + 1] == 'O' && tmp[*i + 2] == ' ')
		&& map->texture_north == NULL)
	{
		map->texture_north = extract_path_texture(tmp, *i);
		return (map->counter++, 0);
	}
	if ((tmp[*i] == 'S' && tmp[*i + 1] == 'O' && tmp[*i + 2] == ' ')
		&& map->texture_south == NULL)
	{
		map->texture_south = extract_path_texture(tmp, *i);
		return (map->counter++, 0);
	}
	if ((tmp[*i] == 'W' && tmp[*i + 1] == 'E' && tmp[*i + 2] == ' ')
		&& map->texture_west == NULL)
	{
		map->texture_west = extract_path_texture(tmp, *i);
		return (map->counter++, 0);
	}
	if ((tmp[*i] == 'E' && tmp[*i + 1] == 'A' && tmp[*i + 2] == ' ')
		&& map->texture_east == NULL)
	{
		map->texture_east = extract_path_texture(tmp, *i);
		return (map->counter++, 0);
	}
	return (1);
}

int	parse_colors(char *tmp, int *i, t_map *map)
{
	int	tmp_color;

	if (tmp[*i] == 'F' && tmp[*i + 1] == ' ' && map->color_floor == -1)
	{
		tmp_color = extract_color(tmp, *i + 1);
		if (tmp_color != -1)
			return (map->color_floor = tmp_color, map->counter++, 0);
		else
			return (write(2, "Error: Wrong color code\n", 24), 1);
	}
	if (tmp[*i] == 'C' && tmp[*i + 1] == ' ' && map->color_sky == -1)
	{
		tmp_color = extract_color(tmp, *i + 1);
		if (tmp_color != -1)
			return (map->color_sky = tmp_color, map->counter++, 0);
		else
			return (write(2, "Error: Wrong color code\n", 24), 1);
	}
	return (1);
}
