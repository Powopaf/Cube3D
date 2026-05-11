/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 20:12:50 by sbrochar          #+#    #+#             */
/*   Updated: 2026/05/11 20:54:03 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error/error.h"
#include "Game/game.h"
#include "Game/key.h"
#include "Render/casting.h"
#include "minilibx-linux/mlx.h"
#include "struct.h"
#include <stdlib.h>
#include <string.h>

static void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}
static void	free_mlx(t_p *p)
{
	if (p->sprite[0].img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->sprite[0].img);
	if (p->sprite[1].img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->sprite[1].img);
	if (p->sprite[2].img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->sprite[2].img);
	if (p->sprite[3].img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->sprite[3].img);
	if (p->data_struct->img != NULL)
		mlx_destroy_image(p->data_struct->mlx, p->data_struct->img);
	if (p->data_struct->win != NULL)
		mlx_destroy_window(p->data_struct->mlx, p->data_struct->win);
	mlx_destroy_display(p->data_struct->mlx);
	free(p->data_struct->mlx);
}
/*
 * mlx_mouse_hide leak
 * link to issue: https://github.com/42paris/minilibx-linux/issues/48
 */

int	run(t_map *map)
{
	t_data	img;
	t_p		p;

	ft_bzero(&img, sizeof(t_data));
	ft_bzero(&p, sizeof(t_p));
	if (init(map, &p, &img) == -1)
		return (-1);
	img.mlx = mlx_init();
	if (!img.mlx)
		return (print_error(ERROR_MLX_INIT));
	img.win = mlx_new_window(img.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!img.win)
		return (print_error(ERROR_WINDOW_INIT));
	img.img = mlx_new_image(img.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img.img)
		return (print_error(ERROR_IMAGE_INIT));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	if (!img.addr)
		return (print_error(ERROR_IMAGE_INIT));
	if (init_spite(map, &p) != 0)
		return (free_mlx(&p), -1);
	// mlx_mouse_hide(img.mlx, img.win);
	game_loop(&p, &img);
	return (0);
}
