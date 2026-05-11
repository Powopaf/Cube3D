/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 21:14:05 by sbrochar          #+#    #+#             */
/*   Updated: 2026/05/10 22:13:21 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error/error.h"
#include "Game/game.h"
#include "Game/key.h"
#include "Render/casting.h"
#include "Include/Game/window.h"
#include "minilibx-linux/mlx.h"
#include "struct.h"

void	game_loop(t_p *p, t_data *img)
{
	mlx_hook(img->win, 6, 1L << 6, mouse_press, p);
	mlx_hook(img->win, 2, 1L << 0, key_press, p);
	mlx_hook(img->win, 3, 1L << 1, key_release, p);
	mlx_hook(img->win, 17, 0, close_window, p);
	mlx_loop_hook(img->mlx, key_loop, p);
	mlx_loop(img->mlx);
}
