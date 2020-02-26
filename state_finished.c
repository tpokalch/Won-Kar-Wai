/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_finished.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:38:26 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:24:20 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	state_finished_update(t_2048 *ctx_2048, int ch)
{
	t_window	*win;

	win = ctx_2048->state_priv[GAME_STATE_FINISHED];
	if (!win)
		return ;
	if (ch != 0)
	{
		SET_STATE(ctx_2048, GAME_STATE_EXIT);
		delwin(win);
		ctx_2048->state_priv[GAME_STATE_FINISHED] = NULL;
	}
	refresh();
}

void	state_finished_render(t_2048 *ctx_2048)
{
	t_window	*win;
	int			x;
	int			y;

	win = ctx_2048->state_priv[GAME_STATE_FINISHED];
	if (!win)
	{
		win = newwin((ctx_2048->screen.height / 3),
					(ctx_2048->screen.width / 3),
				(ctx_2048->screen.height - (ctx_2048->screen.height / 3)) / 2,
				(ctx_2048->screen.width - (ctx_2048->screen.width / 3)) / 2);
		ctx_2048->state_priv[GAME_STATE_FINISHED] = win;
	}
	getmaxyx(win, y, x);
	mvwprintw(win, y / 2 ? y / 2 - 1 : 0, 3, ctx_2048->player_won ?
			"You won!" : "You've lost!");
	mvwprintw(win, y / 2 ? y / 2 : 0, 3, "Press any button to continue.");
	box(win, 0, 0);
	wrefresh(win);
}
