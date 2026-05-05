/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:12:38 by pifourni          #+#    #+#             */
/*   Updated: 2026/05/04 14:45:46 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error/error.h"
#include "Game/game.h"
#include "Game/key.h"
#include "Render/casting.h"
#include "minilibx-linux/mlx.h"
#include "struct.h"

static int load_spite(t_p *p, t_map *map, int index)
{
	p->sprite[index].img = mlx_xpm_file_to_image(p->data_struct->mlx,
			map->texture_north, &p->sprite[index].width,
			&p->sprite[index].height);
	if (!p->sprite[index].img)
		return (print_error(ERROR_TEXTURE));
	p->sprite[index].texture = mlx_get_data_addr(p->sprite[index].img,
			&p->sprite[index].bpp, &p->sprite[index].line_length,
			&p->sprite[index].endian);
	if (!p->sprite[index].texture)
		return (print_error(ERROR_TEXTURE));
	return (0);
}

static int	init_spite(t_map *map, t_p *p)
{
	int	index;

	index = 0;
	while (index < 4)
	{
		if (load_spite(p, map, index) == -1)
			return (-1);
		index++;
	}
	return (0);
}

static int	init(t_map *map, t_p *p, t_data *img)
{
	map->tile_size = min(SCREEN_WIDTH / map->map_width, SCREEN_HEIGHT
			/ map->map_height);
	p->x = map->position_player_x * map->tile_size + map->tile_size / 2.0;
	p->y = map->position_player_y * map->tile_size + map->tile_size / 2.0;
	p->speed = map->tile_size / 10.0;
	p->map = map->map;
	p->tile_size = map->tile_size;
	p->map_struct = map;
	p->data_struct = img;
	if (map->player_orientation == 'N')
		p->angle = -PI / 2.0;
	else if (map->player_orientation == 'S')
		p->angle = PI / 2.0;
	else if (map->player_orientation == 'E')
		p->angle = 0.0;
	else if (map->player_orientation == 'W')
		p->angle = PI;
	else
		return (-1);
	return (0);
}

static void	game_loop(t_p *p, t_data *img)
{
	mlx_hook(img->win, 6, 1L << 6, mouse_press, p);
	mlx_hook(img->win, 2, 1L << 0, key_press, p);
	mlx_hook(img->win, 3, 1L << 1, key_release, p);
	mlx_loop_hook(img->mlx, key_loop, p);
	mlx_loop(img->mlx);
}

/*
* mlx_mouse_hide leak
* link to issue: https://github.com/42paris/minilibx-linux/issues/48
*/

int	run(t_map *map)
{
	t_data	img;
	t_p		p;

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
	if (init_spite(map, &p) == -1)
		return (-1);
	//mlx_mouse_hide(img.mlx, img.win);
	game_loop(&p, &img);
	return (0);
}
