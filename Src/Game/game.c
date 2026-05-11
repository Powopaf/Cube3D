/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/10 12:12:38 by pifourni          #+#    #+#             */
/*   Updated: 2026/05/11 20:50:13 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Error/error.h"
#include "Game/game.h"
#include "Game/key.h"
#include "Render/casting.h"
#include "minilibx-linux/mlx.h"
#include "struct.h"
#include <string.h>

static char	*get_sprite_path(t_map *map, int index)
{
	if (index == 0)
		return (map->texture_north);
	if (index == 1)
		return (map->texture_south);
	if (index == 2)
		return (map->texture_east);
	return (map->texture_west);
}

static int	load_spite(t_p *p, t_map *map, int index)
{
	char	*path;

	path = get_sprite_path(map, index);
	p->sprite[index].img = mlx_xpm_file_to_image(p->data_struct->mlx, path,
			&p->sprite[index].width, &p->sprite[index].height);
	if (!p->sprite[index].img)
		return (print_error(ERROR_TEXTURE));
	p->sprite[index].texture = mlx_get_data_addr(p->sprite[index].img,
			&p->sprite[index].bpp, &p->sprite[index].line_length,
			&p->sprite[index].endian);
	if (!p->sprite[index].texture)
		return (print_error(ERROR_TEXTURE));
	return (0);
}

int	init_spite(t_map *map, t_p *p)
{
	int	index;

	index = 0;
	while (index < 4)
	{
		if (load_spite(p, map, index) != 0)
			return (-1);
		index++;
	}
	return (0);
}

int	init(t_map *map, t_p *p, t_data *img)
{
	map->tile_size = FIXED_TILE_SIZE;
	p->x = map->position_player_x * map->tile_size + map->tile_size / 2.0;
	p->y = map->position_player_y * map->tile_size + map->tile_size / 2.0;
	p->speed = FIXED_SPEED;
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




