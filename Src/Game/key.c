/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:45:07 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/14 20:10:24 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game/key.h"
#include "Game/window.h"
#include <math.h>

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

int	key_press(int keycode, t_p *p)
{
	t_p	*p;

	p = (t_p *)param;
	if (keycode == KEY_DOWN)
		move_player(p, p->angle);
	else if (keycode == KEY_UP)
		move_player(p, p->angle + PI);
	else if (keycode == KEY_LEFT)
		move_player(p, p->angle - PI / 2.0);
	else if (keycode == KEY_RIGHT)
		move_player(p, p->angle + PI / 2.0);
	else if (keycode == KEY_ESC)
		close_window(p);
	return (0);
}

void	mouse_press(int x, int y, void *param)
{
	t_p		*p;
	double	d_x;

	p = (t_p *)param;
	d_x = (double)x - (SCREEN_WIDTH / 2.0);
	p->angle += d_x * SENSITIVITY;
}
