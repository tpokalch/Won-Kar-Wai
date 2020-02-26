/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swipe.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 18:45:37 by tpokalch          #+#    #+#             */
/*   Updated: 2019/01/13 23:39:14 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

void	swap_column(int cln, t_ull **a)
{
	int i;
	int temp;

	i = 0;
	while (i < MAP_SIDE_SIZE / 2)
	{
		temp = *(*(a + i) + cln);
		*(*(a + i) + cln) = *(*(a + MAP_SIDE_SIZE - 1 - i) + cln);
		*(*(a + MAP_SIDE_SIZE - 1 - i) + cln) = temp;
		i++;
	}
}

t_ull	**add_column_up(int cln, t_ull **line, int leftof)
{
	int n_num;

	n_num = next_num_ar(leftof, cln, line);
	if (*(*(line) + cln) == *(*(line + next_num_ar(leftof, cln, line)) + cln))
	{
		*(*line + cln) = *(*line + cln) +
			*(*(line + next_num_ar(leftof, cln, line)) + cln);
		*(*(line + next_num_ar(leftof, cln, line)) + cln) = 0;
	}
	leftof = leftof - n_num;
	if (leftof > 0)
		add_column_up(cln, line + n_num, leftof);
	return (line);
}

t_ull	**compress_column(int cln, t_ull **a)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < MAP_SIDE_SIZE)
	{
		while (*(*(a + i) + cln) == 0 && i < MAP_SIDE_SIZE)
			i++;
		if (i >= (MAP_SIDE_SIZE))
			break ;
		*(*(a + j) + cln) = *(*(a + i) + cln);
		if (i > 0 && i != j)
			*(*(a + i) + cln) = 0;
		j++;
		i++;
	}
	return (a);
}

t_ull	**move_column(int cln, t_ull **a, t_dir swp)
{
	if (swp == UP)
	{
		add_column_up(cln, a, MAP_SIDE_SIZE);
		return (compress_column(cln, a));
	}
	else
	{
		swap_column(cln, a);
		add_column_up(cln, a, MAP_SIDE_SIZE);
		compress_column(cln, a);
		swap_column(cln, a);
		return (a);
	}
	return (a);
}

t_ull	**swipe(t_ull **a, t_dir swp)
{
	t_ull	**sav;
	int		i;
	int		j;

	i = 0;
	j = 0;
	sav = a;
	if (swp == LEFT || swp == RIGHT)
	{
		while (i < MAP_SIDE_SIZE)
		{
			move_line((*(a + i)), swp);
			i++;
		}
		return (sav);
	}
	else if (swp == UP || swp == DOWN)
	{
		while (i < MAP_SIDE_SIZE)
		{
			move_column(i, a, swp);
			i++;
		}
	}
	return (sav);
}
