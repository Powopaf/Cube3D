#include "struct.h"
#include "Render/game.h"

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
		return (-1); // invalid player orientation
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
}