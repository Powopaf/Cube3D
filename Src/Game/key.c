/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:45:07 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/14 10:05:19 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game/key.h"
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

void	key_press(int keycode, void *param)
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
		// exit the game here
		return ;
	else
		return ;
}

void	mouse_press(int x, int y, void *param)
{
}
