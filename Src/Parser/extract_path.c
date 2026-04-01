/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:23:59 by sbrochar          #+#    #+#             */
/*   Updated: 2026/04/01 18:48:03 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../gnl.h"
#include "../parser.h"
#include <unistd.h>

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

int	extract_color(char *tmp, int i)
{
	int	rgb[3];
	int	index_tmp;
	int	j;

	j = 0;
	i++;
	while (j < 3)
	{
		while (tmp[i] == ' ')
			i++;
		index_tmp = i;
		rgb[j] = atoi_color(0, &i, tmp);
		if (i == index_tmp || rgb[j] > 255)
			return (-1);
		while (tmp[i] == ' ')
			i++;
		if (j < 2 && tmp[i] != ',')
			return (-1);
		if (j < 2)
			i++;
		j++;
	}
	if (tmp[i] != '\n' && tmp[i] != '\0')
		return (-1);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}

int	count_line_map(char *tmp, t_map *map)
{
	int	i;

	i = 0;
	while (tmp[i] == ' ')
		i++;
	if (parse_texture(tmp, &i, map) == 0)
		return (0);
	if (parse_colors(tmp, &i, map) == 0)
		return (0);
	if (tmp[i] == '\n' || tmp[i] == '\0')
		return (0);
	return (write(2, "Error: Invalid parsing for texture or color\n", 44), 1);
}
