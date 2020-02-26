/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finished.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:49:47 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 22:19:56 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

bool	has_lost(t_2048 *ctx_2048)
{
	return (!map_has_empty_tiles(&ctx_2048->map) &&
			!movement(ctx_2048->map.tiles, UP) &&
			!movement(ctx_2048->map.tiles, DOWN) &&
			!movement(ctx_2048->map.tiles, LEFT) &&
			!movement(ctx_2048->map.tiles, RIGHT));
}

bool	has_won(t_2048 *ctx_2048)
{
	int		y;
	int		x;

	y = 0;
	while (y < MAP_SIDE_SIZE)
	{
		x = 0;
		while (x < MAP_SIDE_SIZE)
		{
			if (ctx_2048->map.tiles[y][x] == WIN_VALUE)
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}
