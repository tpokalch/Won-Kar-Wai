/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 19:25:40 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:16:14 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	set_state_functions(t_2048 *ctx_2048)
{
	int i;

	ctx_2048->update_fns[GAME_STATE_START] = state_start_update;
	ctx_2048->render_fns[GAME_STATE_START] = state_start_render;
	ctx_2048->update_fns[GAME_STATE_IN_PROGRESS] = state_in_progress_update;
	ctx_2048->render_fns[GAME_STATE_IN_PROGRESS] = state_in_progress_render;
	ctx_2048->update_fns[GAME_STATE_PAUSED] = state_paused_update;
	ctx_2048->render_fns[GAME_STATE_PAUSED] = state_paused_render;
	ctx_2048->update_fns[GAME_STATE_FINISHED] = state_finished_update;
	ctx_2048->render_fns[GAME_STATE_FINISHED] = state_finished_render;
	ctx_2048->update_fns[GAME_STATE_EXIT] = state_exit_update;
	ctx_2048->render_fns[GAME_STATE_EXIT] = state_exit_render;
	i = 0;
	while (i < GAME_STATE_MAX)
	{
		ctx_2048->resize_fns[i] = NULL;
		i++;
	}
}
