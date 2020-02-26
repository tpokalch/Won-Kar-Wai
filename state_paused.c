/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_paused.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:37:50 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:33:18 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	state_paused_update(t_2048 *ctx_2048, int ch)
{
	t_window	*win;

	win = ctx_2048->state_priv[GAME_STATE_PAUSED];
	if (!win)
		return ;
	if (ch == 'N' || ch == 'n')
	{
		SET_STATE(ctx_2048, GAME_STATE_IN_PROGRESS);
		delwin(win);
		ctx_2048->state_priv[GAME_STATE_PAUSED] = NULL;
	}
	else if (ch == 'Y' || ch == 'y')
	{
		SET_STATE(ctx_2048, GAME_STATE_EXIT);
		ctx_2048->keep_playing = true;
		delwin(win);
		ctx_2048->state_priv[GAME_STATE_PAUSED] = NULL;
	}
	refresh();
}

void	state_paused_render(t_2048 *ctx_2048)
{
	int			x;
	int			y;
	t_window	*win;

	win = ctx_2048->state_priv[GAME_STATE_PAUSED];
	if (!win)
	{
		win = newwin((ctx_2048->screen.height / 3),
					(ctx_2048->screen.width / 3),
				(ctx_2048->screen.height - (ctx_2048->screen.height / 3)) / 2,
				(ctx_2048->screen.width - (ctx_2048->screen.width / 3)) / 2);
		ctx_2048->state_priv[GAME_STATE_PAUSED] = win;
	}
	getmaxyx(win, y, x);
	mvwprintw(win, y / 2 ? y / 2 - 1 : 0, 3, "Paused.");
	mvwprintw(win, y / 2 ? y / 2 : 0, 3, "Want to end the game? Y/N");
	box(win, 0, 0);
	wrefresh(win);
}
