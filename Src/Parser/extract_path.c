/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 17:23:59 by sbrochar          #+#    #+#             */
/*   Updated: 2026/05/12 15:52:33 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/gnl.h"
#include "Parser/parser.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static int	valid_path(char *filename)
{
	int	len;

	if (!filename)
		return (1);
	len = ft_strlen(filename);
	if (len < 5)
		return (1);
	if (filename[len - 4] == '.' && filename[len - 3] == 'x' && filename[len
			- 2] == 'p' && filename[len - 1] == 'm')
		return (0);
	return (1);
}

static char	*valid_fd(char *path)
{
	int	fd;

	fd = open(path, __O_DIRECTORY);
	if (fd != -1)
		return (write(2, "Error: This is a folder, not a file\n", 36),
			free(path), NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error: The file cannot be opened\n", 33), free(path),
			NULL);
	close(fd);
	return (path);
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
	if (valid_path(path) == 1)
		return (write(2, "Error: Invalid extension or path format\n", 40),
			free(path), NULL);
	return (valid_fd(path));
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
	int	status;

	status = 0;
	i = 0;
	while (tmp[i] == ' ')
		i++;
	status = parse_texture(tmp, &i, map);
	if (status == 0)
		return (0);
	if (status == 1)
		return (1);
	status = parse_colors(tmp, &i, map);
	if (status == 0)
		return (0);
	if (status == 1)
		return (1);
	if (tmp[i] == '\n' || tmp[i] == '\0')
		return (0);
	write(2, "Error: An element is not positioned correctly or is duplicated\n",
		63);
	return (1);
}
