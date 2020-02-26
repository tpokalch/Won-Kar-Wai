/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swipe3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 23:37:44 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:38:19 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

t_ull	*move_line(t_ull *a, t_dir swp)
{
	t_ull *save;

	save = a;
	if (swp == LEFT)
	{
		add_line_left(a, MAP_SIDE_SIZE);
		return (compress_line(a));
	}
	else
	{
		swap_line(a);
		add_line_left(a, MAP_SIDE_SIZE);
		compress_line(a);
		(swap_line(a));
		return (a);
	}
}

int		next_num_ar(int leftof, int cln, t_ull **line)
{
	int i;

	i = 1;
	while (*(*(line + i) + cln) == 0 && i < leftof)
		i++;
	if (i == MAP_SIDE_SIZE)
		return (MAP_SIDE_SIZE);
	return (i);
}
