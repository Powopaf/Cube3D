/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 21:55:12 by sbrochar          #+#    #+#             */
/*   Updated: 2026/05/12 12:50:47 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "GNL/gnl.h"
#include "Parser/parser.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_iswhitespace(char c)
{
	if (c == 32 || (c >= 7 && c <= 9))
		return (1);
	return (0);
}

int	empty_line(char *line)
{
	int	i;

	i = 0;
	while (ft_iswhitespace(line[i]) == 1)
		i++;
	if (line[i] == '\n' || line[i] == '\0')
		return (1);
	return (0);
}

size_t	strlen_for_tab(char *str)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			count += 4;
		else
			count += 1;
		i++;
	}
	return (count);
}
