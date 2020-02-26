/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:45:54 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:32:04 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

bool		map_has_empty_tiles(t_2048_map *map)
{
	int		x;
	int		y;

	y = 0;
	while (y < MAP_SIDE_SIZE)
	{
		x = 0;
		while (x < MAP_SIDE_SIZE)
		{
			if (map->tiles[y][x] == 0)
				return (true);
			x++;
		}
		y++;
	}
	return (false);
}

void		map_add_random_value(t_2048_map *map)
{
	int		x;
	int		y;

	if (!map_has_empty_tiles(map))
		return ;
	while (1)
	{
		x = RANDOM_IDX();
		y = RANDOM_IDX();
		if (map->tiles[y][x] != 0)
			continue ;
		map->tiles[y][x] = TILE_RANDOM_VALUE();
		return ;
	}
}

static void	map_fill_initial_values(t_2048_map *map)
{
	int		filled;

	filled = 0;
	while (filled != INITIALIZED_TILES)
	{
		map_add_random_value(map);
		filled++;
	}
}

void		map_init(t_2048_map *map)
{
	int		y;
	int		x;

	map->tiles = (t_ull**)malloc(sizeof(*map->tiles)
			* (MAP_SIDE_SIZE + 1));
	y = 0;
	while (y < MAP_SIDE_SIZE + 1)
	{
		map->tiles[y] = (t_ull*)malloc(sizeof(*map->tiles[0])
				* (MAP_SIDE_SIZE + 1));
		x = 0;
		while (x < MAP_SIDE_SIZE)
		{
			map->tiles[y][x] = 0;
			x++;
		}
		y++;
	}
	map_fill_initial_values(map);
}

void		init_grid(t_2048 *ctx_2048)
{
	int	x;
	int	y;

	refresh();
	getmaxyx(stdscr, ctx_2048->screen.height, ctx_2048->screen.width);
	y = 0;
	while (y < MAP_SIDE_SIZE)
	{
		x = 0;
		while (x < MAP_SIDE_SIZE)
		{
			ctx_2048->map_tiles[y][x].value = &ctx_2048->map.tiles[y][x];
			tile_set_position(&ctx_2048->map_tiles[y][x],
							&ctx_2048->screen, x, y);
			tile_init_window(&ctx_2048->map_tiles[y][x]);
			x++;
		}
		y++;
	}
}
