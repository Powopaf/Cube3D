/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrochar <sbrochar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 13:44:27 by pifourni          #+#    #+#             */
/*   Updated: 2026/05/10 21:15:05 by sbrochar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# define FIXED_TILE_SIZE 16
# define FIXED_SPEED 4

# include "struct.h"

int		run(t_map *map);
void	game_loop(t_p *p, t_data *img);

#endif
