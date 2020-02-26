/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:07:00 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:33:40 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	state_start_update(t_2048 *ctx_2048, int ch)
{
	t_window	*win;

	win = ctx_2048->state_priv[GAME_STATE_START];
	if (!win)
		return ;
	if (ch == 'Y' || ch == 'y')
	{
		SET_STATE(ctx_2048, GAME_STATE_IN_PROGRESS);
		delwin(win);
		ctx_2048->state_priv[GAME_STATE_START] = NULL;
	}
	else if (ch == 'N' || ch == 'n' || ch == 'q' || ch == KEY_EXIT)
	{
		SET_STATE(ctx_2048, GAME_STATE_EXIT);
		ctx_2048->keep_playing = false;
		delwin(win);
		ctx_2048->state_priv[GAME_STATE_START] = NULL;
	}
	refresh();
}

void	state_start_render(t_2048 *ctx_2048)
{
	t_window	*win;
	int			x;
	int			y;

	win = ctx_2048->state_priv[GAME_STATE_START];
	if (!win)
	{
		win = newwin((ctx_2048->screen.height / 3),
					(ctx_2048->screen.width / 3),
				(ctx_2048->screen.height - (ctx_2048->screen.height / 3)) / 2,
				(ctx_2048->screen.width - (ctx_2048->screen.width / 3)) / 2);
		ctx_2048->state_priv[GAME_STATE_START] = win;
	}
	getmaxyx(win, y, x);
	mvwprintw(win, y / 2 ? y / 2 - 1 : 0, 3,
			"Welcome! Want to start a game? Y/N");
	box(win, 0, 0);
	wrefresh(win);
}
