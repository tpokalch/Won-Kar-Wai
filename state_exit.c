/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:36:41 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:22:33 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	state_exit_update(t_2048 *ctx_2048, int ch)
{
	UNUSED(ctx_2048);
	UNUSED(ch);
}

void	state_exit_render(t_2048 *ctx_2048)
{
	int			x;
	int			y;
	t_window	*win;

	if (ctx_2048->keep_playing)
		return ;
	win = newwin((ctx_2048->screen.height * 3) / 2,
				(ctx_2048->screen.width * 3) / 2,
				ctx_2048->screen.height / 3,
				ctx_2048->screen.width / 3);
	getmaxyx(win, y, x);
	mvwprintw(win, y / 2, x / 5, "Exiting...");
	box(win, 0, 0);
	wrefresh(win);
}
