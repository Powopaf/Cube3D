/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 10:42:22 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/20 15:15:42 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game/game.h"
#include "Parser/parser.h"

int	main(int argc, char **argv)
{
	t_map	map;

	if (parsing(&map, argv, argc) == 1)
		return (1);
	run(&map);
	return (0);
}
