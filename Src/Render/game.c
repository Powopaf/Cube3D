/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pifourni <pifourni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:12:38 by pifourni          #+#    #+#             */
/*   Updated: 2026/04/13 13:23:30 by pifourni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "struct.h"
#include "Render/game.h"
#include "Error/error.h"
#include "mlx.h"

static int	init(t_map *map, t_p *p)
{
	map->tile_size = min(SCREEN_WIDTH / map->map_width, SCREEN_HEIGHT / map->map_height);
	p->x = map->position_player_x * map->tile_size + map->tile_size / 2.0;
	p->y = map->position_player_y * map->tile_size + map->tile_size / 2.0;
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

static int	game_loop(t_map *map, t_p *p, t_data *img)
{
	return (0);
}

int run(t_map *map)
{
	void *mlx;
	void *win;
	t_data img;
	t_p p;

	if (init(map, &p) == -1)
		return (-1);
	mlx = mlx_init();
	if (!mlx)
		return (print_error(ERROR_MLX_INIT));
	win = mlx_new_window(mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "Cub3D");
	if (!win)
		return (print_error(ERROR_WINDOW_INIT));
	img.img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img.img)
		return (print_error(ERROR_IMAGE_INIT));
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	if (!img.addr)
		return (print_error(ERROR_IMAGE_INIT));
}
