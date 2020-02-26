/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 18:45:46 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:31:31 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	main_loop(t_2048 *ctx_2048)
{
	int			ch;

	ch = 0;
	ctx_2048->update_fns[GET_STATE(ctx_2048)](ctx_2048, ch);
	ctx_2048->render_fns[GET_STATE(ctx_2048)](ctx_2048);
	render_layout(ctx_2048);
	while (GET_STATE(ctx_2048) != GAME_STATE_EXIT)
	{
		ch = getch();
		if (ch == KEY_RESIZE)
			resize_2048(ctx_2048);
		ctx_2048->update_fns[GET_STATE(ctx_2048)](ctx_2048, ch);
		ctx_2048->render_fns[GET_STATE(ctx_2048)](ctx_2048);
		render_layout(ctx_2048);
	}
}

void	game_start(t_2048 *ctx_2048)
{
	SET_STATE(ctx_2048, GAME_STATE_START);
	map_init(&ctx_2048->map);
	init_grid(ctx_2048);
	main_loop(ctx_2048);
}

void	game_cleanup(t_2048 *ctx_2048)
{
	int	x;
	int	y;

	y = 0;
	while (y < MAP_SIDE_SIZE)
	{
		x = 0;
		while (x < MAP_SIDE_SIZE)
		{
			delwin(ctx_2048->map_tiles[y][x].win);
			ctx_2048->map_tiles[y][x].win = NULL;
			x++;
		}
		free(ctx_2048->map.tiles[y]);
		ctx_2048->map.tiles[y] = NULL;
		y++;
	}
	free(ctx_2048->map.tiles);
	ctx_2048->map.tiles = NULL;
}

void	init_ctx(t_2048 *ctx_2048)
{
	int		i;

	ctx_2048->keep_playing = true;
	getmaxyx(stdscr, ctx_2048->screen.height, ctx_2048->screen.width);
	SET_STATE(ctx_2048, GAME_STATE_START);
	i = 0;
	while (i < GAME_STATE_MAX)
	{
		ctx_2048->state_priv[i] = NULL;
		i++;
	}
	ctx_2048->player_won = false;
	set_state_functions(ctx_2048);
}

int		main(int argc, char **argv)
{
	t_2048	ctx_2048;

	(void)argc;
	if (WIN_VALUE % 2 != 0)
	{
		write(1, "WIN_VALUE has to be a power of 2.", 33);
		return (1);
	}
	initscr();
	noecho();
	cbreak();
	curs_set(0);
	keypad(stdscr, TRUE);
	srand((int)argv);
	init_ctx(&ctx_2048);
	while (ctx_2048.keep_playing)
	{
		game_start(&ctx_2048);
		game_cleanup(&ctx_2048);
	}
	endwin();
}
