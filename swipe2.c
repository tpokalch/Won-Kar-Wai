/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swipe2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elyahove <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 23:35:03 by elyahove          #+#    #+#             */
/*   Updated: 2019/01/13 23:37:19 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

int		next_num(int leftof, t_ull *s)
{
	int i;

	i = 1;
	while (*(s + i) == 0 && i < leftof)
	{
		i++;
	}
	return (i);
}

int		first_zero(int *a)
{
	int i;

	i = 0;
	while (*(a + i) && i < MAP_SIDE_SIZE != 0)
		i++;
	if (i == MAP_SIDE_SIZE)
		return (-1);
	return (i);
}

void	swap_line(t_ull *line)
{
	int		i;
	t_ull	temp;

	i = 0;
	while (i < MAP_SIDE_SIZE / 2)
	{
		temp = *(line + i);
		*(line + i) = *(line + MAP_SIDE_SIZE - 1 - i);
		*(line + MAP_SIDE_SIZE - 1 - i) = temp;
		i++;
	}
}

t_ull	*compress_line(t_ull *a)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < MAP_SIDE_SIZE)
	{
		while (*(a + i) == 0 && i < MAP_SIDE_SIZE)
			i++;
		if (i >= (MAP_SIDE_SIZE))
			break ;
		*(a + j) = *(a + i);
		if (i > 0 && i != j)
			*(a + i) = 0;
		j++;
		i++;
	}
	return (a);
}

t_ull	*add_line_left(t_ull *line, int leftof)
{
	t_ull n_num;

	n_num = next_num(leftof, line);
	if (*(line) == *(line + n_num))
	{
		*(line) = *(line) + *(line + n_num);
		*(line + n_num) = 0;
	}
	leftof = leftof - n_num;
	if (leftof > 0)
		add_line_left(line + n_num, leftof);
	return (line);
}
