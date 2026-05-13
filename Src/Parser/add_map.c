/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 19:13:17 by sbrochar          #+#    #+#             */
/*   Updated: 2026/05/11 22:25:43 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/gnl.h"
#include "Parser/parser.h"
#include <stdlib.h>
#include <unistd.h>

static void	put_spaces(char *newstr, size_t *j)
{
	int	n;

	n = 0;
	while (n++ < 4)
		newstr[(*j)++] = ' ';
}

char	*ft_substr_for_tab(char const *str, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	size;

	(void)len;
	if (!str || start >= ft_strlen(str))
		return (ft_strdup(""));
	size = strlen_for_tab((char *)&str[start]);
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = start;
	j = 0;
	while (str[i] && j < size)
	{
		if (str[i] == '\t' && j + 4 <= size)
			put_spaces(new, &j);
		else if (str[i] != '\t')
			new[j++] = str[i];
		i++;
	}
	return (new[j] = '\0', new);
}

void	add_node_map(t_map *map, char *new_line)
{
	t_node_map	*new_node;
	t_node_map	*current;

	new_node = malloc(sizeof(t_node_map));
	if (!new_node)
	{
		free(new_line);
		return ;
	}
	new_node->read_line = new_line;
	new_node->next = NULL;
	if (map->node_map == NULL)
		map->node_map = new_node;
	else
	{
		current = map->node_map;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
	}
}

int	add_map_line(t_map *map, char *line)
{
	int		len;
	char	*new_line;

	if (!line)
		return (1);
	len = 0;
	while (line[len] && line[len] != '\n')
		len++;
	if (len == 0 || empty_line(line) == 1)
	{
		if (map->map_height > 0)
			map->map_lock = 1;
		return (0);
	}
	if (map->map_lock == 1)
		return (write(2, "Error: Empty line inside the map\n", 33), 1);
	new_line = ft_substr_for_tab(line, 0, strlen_for_tab(line));
	if (map->map_width < (int)ft_strlen(new_line))
		map->map_width = ft_strlen(new_line);
	add_node_map(map, new_line);
	map->map_height++;
	return (0);
}
