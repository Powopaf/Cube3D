/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 16:37:31 by sbrochar          #+#    #+#             */
/*   Updated: 2026/05/11 19:26:03 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/Parser/parser.h"
#include "Include/struct.h"
#include "minilibx-linux/mlx.h"
#include <stdlib.h>

static void	exit_game(t_p *p)
{
	if (p->sprite[0].img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->sprite[0].img);
	if (p->sprite[1].img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->sprite[1].img);
	if (p->sprite[2].img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->sprite[2].img);
	if (p->sprite[3].img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->sprite[3].img);
	mlx_destroy_window(p->data_struct->mlx, p->data_struct->win);
	if (p->data_struct->img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->data_struct->img);
	mlx_loop_end(p->data_struct->mlx);
	mlx_destroy_display(p->data_struct->mlx);
	free(p->data_struct->mlx);
	free_all_map(p->map_struct);
	exit(0);
}

int	close_window(t_p *p)
{
	exit_game(p);
	return (0);
}
