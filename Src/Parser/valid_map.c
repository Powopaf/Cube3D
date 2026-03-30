/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 15:51:07 by sbrochar          #+#    #+#             */
/*   Updated: 2026/03/30 17:25:46 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parser.h"

bool	valid_extension(char *filename)
{
	int	len;

	if (!filename)
		return (false);
	len = ft_strlen(filename);
	if (len < 5)
		return (false);
	if (filename[len - 4] == '.' && filename[len - 3] == 'c' && filename[len
			- 2] == 'u' && filename[len - 1] == 'b')
		return (true);
	return (false);
}