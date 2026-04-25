/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:45:07 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/20 15:03:12 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game/key.h"
#include "Game/window.h"
#include "Render/casting.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

static int	g_up;
static int	g_down;
static int	g_left;
static int	g_right;

static void	move_player(t_p *p, double angle_offset)
{
	double	old_x;
	double	old_y;
	int		new_x;
	int		new_y;

	old_x = p->x;
	old_y = p->y;
	p->x += cos(angle_offset) * p->speed;
	p->y += sin(angle_offset) * p->speed;
	new_x = (int)(p->x / (double)p->tile_size);
	new_y = (int)(p->y / (double)p->tile_size);
	if (p->map[new_y][new_x] == '1')
	{
		p->x = old_x;
		p->y = old_y;
	}
}

int	key_press(int keycode, void *param)
{
	t_p	*p;

	p = (t_p *)param;
	if (keycode == KEY_UP)
		g_up = 1;
	else if (keycode == KEY_DOWN)
		g_down = 1;
	else if (keycode == KEY_LEFT)
		g_left = 1;
	else if (keycode == KEY_RIGHT)
		g_right = 1;
	else if (keycode == KEY_ESC)
		close_window(p);
	return (0);
}

int	key_release(int keycode, void *param)
{
	(void)param;
	if (keycode == KEY_UP)
		g_up = 0;
	else if (keycode == KEY_DOWN)
		g_down = 0;
	else if (keycode == KEY_LEFT)
		g_left = 0;
	else if (keycode == KEY_RIGHT)
		g_right = 0;
	return (0);
}

int	key_loop(void *param)
{
	t_p	*p;

	p = (t_p *)param;
	if (g_up)
		move_player(p, p->angle);
	if (g_down)
		move_player(p, p->angle + PI);
	if (g_left)
		move_player(p, p->angle - PI / 2.0);
	if (g_right)
		move_player(p, p->angle + PI / 2.0);
	render(p);
	mlx_put_image_to_window(p->data_struct->mlx, p->data_struct->win,
		p->data_struct->img, 0, 0);
	return (0);
}

int	mouse_press(int x, int y, void *param)
{
	t_p		*p;
	double	d_x;

	(void)y;
	p = (t_p *)param;
	d_x = (double)x - (SCREEN_WIDTH / 2.0);
	p->angle += d_x * SENSITIVITY;
	mlx_mouse_move(p->data_struct->mlx, p->data_struct->win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	return (0);
}
