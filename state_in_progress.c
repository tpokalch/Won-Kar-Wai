/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_in_progress.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:37:05 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:41:11 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

static bool	check_finished(t_2048 *ctx_2048)
{
	if (has_won(ctx_2048))
	{
		SET_STATE(ctx_2048, GAME_STATE_FINISHED);
		ctx_2048->player_won = true;
		return (true);
	}
	else if (has_lost(ctx_2048))
	{
		SET_STATE(ctx_2048, GAME_STATE_FINISHED);
		ctx_2048->player_won = false;
		return (true);
	}
	return (false);
}

static int	move_tiles(t_2048 *ctx_2048, int ch)
{
	int		moved;
	t_dir	direction;

	moved = 0;
	if (ch == KEY_UP)
		direction = UP;
	else if (ch == KEY_DOWN)
		direction = DOWN;
	else if (ch == KEY_LEFT)
		direction = LEFT;
	else if (ch == KEY_RIGHT)
		direction = RIGHT;
	else
		return (0);
	moved = movement(ctx_2048->map.tiles, direction);
	swipe(ctx_2048->map.tiles, direction);
	return (moved);
}

void		state_in_progress_update(t_2048 *ctx_2048, int ch)
{
	int		moved;

	moved = 0;
	if (ch == KEY_UP || ch == KEY_DOWN || ch == KEY_RIGHT || ch == KEY_LEFT)
		moved = move_tiles(ctx_2048, ch);
	else if (ch == 'p' || ch == KEY_EXIT)
	{
		SET_STATE(ctx_2048, GAME_STATE_PAUSED);
		return ;
	}
	else
		return ;
	if (check_finished(ctx_2048))
		state_in_progress_render(ctx_2048);
	else if (moved)
		map_add_random_value(&ctx_2048->map);
}

void		state_in_progress_render(t_2048 *ctx_2048)
{
	int		y;
	int		x;

	clear();
	refresh();
	y = 0;
	while (y < MAP_SIDE_SIZE)
	{
		x = 0;
		while (x < MAP_SIDE_SIZE)
		{
			wclear(ctx_2048->map_tiles[y][x].win);
			tile_render(&ctx_2048->map_tiles[y][x]);
			x++;
		}
		y++;
	}
}
