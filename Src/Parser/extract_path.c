/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:23:59 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/01 12:17:11 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl.h"
#include "../parser.h"

int	extract_color(char *tmp, int i)
{
	int	r;
	int	g;
	int	b;
	int	index_tmp;

	r = 0;
	g = 0;
	b = 0;
	i++;
	while (tmp[i] == ' ')
		i++;
	index_tmp = i;
	while (tmp[i] >= '0' && tmp[i] <= '9')
	{
		r = (r * 10) + (tmp[i] - '0');
		i++;
	}
	if (i == index_tmp)
	{
		printf("Wrong color code\n");
		return (-1);
	}
	while (tmp[i] == ' ')
		i++;
	if (tmp[i] != ',')
	{
		printf("Wrong color code\n");
		return (-1);
	}
	i++;
	while (tmp[i] == ' ')
		i++;
	index_tmp = i;
	while (tmp[i] >= '0' && tmp[i] <= '9')
	{
		g = (g * 10) + (tmp[i] - '0');
		i++;
	}
	if (i == index_tmp)
	{
		printf("Wrong color code\n");
		return (-1);
	}
	while (tmp[i] == ' ')
		i++;
	if (tmp[i] != ',')
	{
		printf("Wrong color code\n");
		return (-1);
	}
	i++;
	while (tmp[i] == ' ')
		i++;
	index_tmp = i;
	while (tmp[i] >= '0' && tmp[i] <= '9')
	{
		b = (b * 10) + (tmp[i] - '0');
		i++;
	}
	if (i == index_tmp)
	{
		printf("Wrong color code\n");
		return (-1);
	}
	while (tmp[i] == ' ')
		i++;
	if (tmp[i] != '\n' && tmp[i] != '\0')
	{
		printf("Wrong color code\n");
		return (-1);
	}
	if (r > 255 || g > 255 || b > 255)
	{
		printf("Wrong color code\n");
		return (-1);
	}
	return ((r << 16) | (g << 8) | b);
}

char	*extract_path_texture(char *tmp, int i)
{
	int		len_path;
	char	*path;
	int		j;

	i = i + 2;
	len_path = 0;
	while (tmp[i] == ' ')
		i++;
	j = i;
	while (tmp[j] != ' ' && tmp[j] != '\n' && tmp[j] != '\0')
	{
		len_path++;
		j++;
	}
	path = ft_substr(tmp, i, len_path);
	return (path);
}

int	count_line_map(char *tmp, t_map *map)
{
	int	i;
	int	tmp_color;

	i = 0;
	while (tmp[i] == ' ')
		i++;
	if (tmp[i] == 'N' && tmp[i + 1] == 'O' && tmp[i + 2] == ' ')
	{
		if (map->texture_north == NULL)
		{
			map->texture_north = extract_path_texture(tmp, i);
			map->counter++;
			return (0);
		}
	}
	if (tmp[i] == 'S' && tmp[i + 1] == 'O' && tmp[i + 2] == ' ')
	{
		if (map->texture_south == NULL)
		{
			map->texture_south = extract_path_texture(tmp, i);
			map->counter++;
			return (0);
		}
	}
	if (tmp[i] == 'W' && tmp[i + 1] == 'E' && tmp[i + 2] == ' ')
	{
		if (map->texture_west == NULL)
		{
			map->texture_west = extract_path_texture(tmp, i);
			map->counter++;
			return (0);
		}
	}
	if (tmp[i] == 'E' && tmp[i + 1] == 'A' && tmp[i + 2] == ' ')
	{
		if (map->texture_east == NULL)
		{
			map->texture_east = extract_path_texture(tmp, i);
			map->counter++;
			return (0);
		}
	}
	if (tmp[i] == 'F' && tmp[i + 1] == ' ')
	{
		tmp_color = extract_color(tmp, i);
		if (map->color_floor == -1)
		{
			if (tmp_color != -1)
			{
				map->color_floor = tmp_color;
				map->counter++;
				return (0);
			}
			else
				return (1);
		}
	}
	if (tmp[i] == 'C' && tmp[i + 1] == ' ')
	{
		tmp_color = extract_color(tmp, i);
		if (map->color_sky == -1)
		{
			if (tmp_color != -1)
			{
				map->color_sky = tmp_color;
				map->counter++;
				return (0);
			}
			else
				return (1);
		}
	}
	if (tmp[i] == '\n' || tmp[i] == '\0')
		return (0);
	write(2, "Error: Invalid parsing for texture or color\n", 45);
	return (1);
}
