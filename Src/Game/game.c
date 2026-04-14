/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:12:38 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/14 10:04:52 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "Render/ray_casting.h"
#include "Error/error.h"
#include "mlx.h"
#include "Game/key.h"
#include "Game/game.h"

static int	init(t_map *map, t_p *p)
{
	map->tile_size = min(SCREEN_WIDTH / map->map_width, SCREEN_HEIGHT / map->map_height);
	p->x = map->position_player_x * map->tile_size + map->tile_size / 2.0;
	p->y = map->position_player_y * map->tile_size + map->tile_size / 2.0;
	p->speed = map->tile_size / 10.0;
	p->map = map->map;
	p->tile_size = map->tile_size;
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

static void	game_loop(t_map *map, t_p *p, t_data *img)
{
	render(img, *map, *p);
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	mlx_hooks(img->win, 6, 1L << 6, mouse_press, p);
	mlx_hooks(img->win, 2, 1L << 0, key_press, p);
	mlx_loop(img->mlx);
}

int run(t_map *map)
{
	t_data img;
	t_p p;

	if (init(map, &p) == -1)
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
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (!img.addr)
		return (print_error(ERROR_IMAGE_INIT));
	game_loop(map, &p, &img);
	return (0);
}
