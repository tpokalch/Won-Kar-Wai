/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tile.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:45:49 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 19:02:52 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

static int	tile_get_value_width(t_2048_tile_win *tile)
{
	int		value_width;
	int		value;

	value_width = 0;
	value = *tile->value;
	while (value)
	{
		value_width++;
		value /= 10;
	}
	return (value_width);
}

void		tile_render(t_2048_tile_win *tile)
{
	int		value_width;

	value_width = tile_get_value_width(tile);
	if (value_width)
		mvwprintw(tile->win, tile->height ? tile->height / 2 : 0,
			tile->width ? (tile->width - value_width) / 2 : 0, "%d",
			*tile->value);
	box(tile->win, 0, 0);
	wrefresh(tile->win);
}

void		tile_set_position(t_2048_tile_win *tile, t_screen *scr,
								int x, int y)
{
	tile->width = (double)scr->width * TILE_SIDE_SIZE;
	tile->height = (double)scr->height * TILE_SIDE_SIZE;
	tile->pos_x = (double)scr->width * MAP_PADDING +
					x * tile->width +
					x * ((double)scr->width * INTER_TILE_GAP);
	tile->pos_y = (double)scr->height * MAP_PADDING +
					y * tile->height +
					y * ((double)scr->height * INTER_TILE_GAP);
}

void		tile_init_window(t_2048_tile_win *tile)
{
	tile->win = newwin(tile->height, tile->width, tile->pos_y, tile->pos_x);
	tile_render(tile);
}

void		tile_resize_window(t_2048_tile_win *tile)
{
	wclear(tile->win);
	wresize(tile->win, tile->height, tile->width);
	mvwin(tile->win, tile->pos_y, tile->pos_x);
	tile_render(tile);
}
