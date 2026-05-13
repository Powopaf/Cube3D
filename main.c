/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:42:22 by pifourni          #+#    #+#             */
/*   Updated: 2026/05/11 20:10:41 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game/game.h"
#include "Parser/parser.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (parsing(&map, argv, argc) == 1)
		return (1);
	if (run(&map) != 0)
	{
		free_all_map(&map);
		return (1);
	}
	return (0);
}
