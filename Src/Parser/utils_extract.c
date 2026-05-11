/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_extract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 18:01:44 by sbrochar          #+#    #+#             */
/*   Updated: 2026/05/07 20:27:18 by sbrochar         ###   ########.fr       */
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

static int	which_face(char *tmp, int i, char *face, char **path)
{
	if ((tmp[i] == face[0] && tmp[i + 1] == face[1] && tmp[i + 2] == ' ')
		&& *path == NULL)
	{
		*path = extract_path_texture(tmp, i);
		if (*path == NULL)
			return (1);
		return (0);
	}
	return (2);
}

int	parse_texture(char *tmp, int *i, t_map *map)
{
	int	status;

	status = which_face(tmp, *i, "NO", &map->texture_north);
	if (status == 1)
		return (1);
	if (status == 0)
		return (map->counter++, 0);
	status = which_face(tmp, *i, "SO", &map->texture_south);
	if (status == 1)
		return (1);
	if (status == 0)
		return (map->counter++, 0);
	status = which_face(tmp, *i, "WE", &map->texture_west);
	if (status == 1)
		return (1);
	if (status == 0)
		return (map->counter++, 0);
	status = which_face(tmp, *i, "EA", &map->texture_east);
	if (status == 1)
		return (1);
	if (status == 0)
		return (map->counter++, 0);
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
