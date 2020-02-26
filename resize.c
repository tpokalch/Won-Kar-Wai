/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:48:41 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:31:44 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	resize_2048(t_2048 *ctx_2048)
{
	int		x;
	int		y;

	clear();
	refresh();
	getmaxyx(stdscr, ctx_2048->screen.height, ctx_2048->screen.width);
	y = 0;
	while (y < MAP_SIDE_SIZE)
	{
		x = 0;
		while (x < MAP_SIDE_SIZE)
		{
			tile_set_position(&ctx_2048->map_tiles[y][x],
							&ctx_2048->screen, x, y);
			tile_resize_window(&ctx_2048->map_tiles[y][x]);
			x++;
		}
		y++;
	}
	if (ctx_2048->resize_fns[ctx_2048->state])
		ctx_2048->resize_fns[ctx_2048->state](ctx_2048);
}

void	render_layout(t_2048 *ctx_2048)
{
	int		header_y;
	int		header_x;

	header_y = ctx_2048->screen.height * (MAP_PADDING / 2.0f);
	header_x = (ctx_2048->screen.width - 4) / 2;
	if (header_x < 0)
		header_x = 0;
	mvprintw(header_y, header_x, "2048");
}
