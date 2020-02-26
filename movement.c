/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpokalch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 19:34:46 by tpokalch          #+#    #+#             */
/*   Updated: 2019/01/13 23:15:25 by elyahove         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"

static int		tab_cmp(t_ull **old, t_ull **new)
{
	int i;
	int j;

	j = 0;
	while (j < MAP_SIDE_SIZE)
	{
		i = 0;
		while (i < MAP_SIDE_SIZE)
		{
			if (*(*(old + j) + i) != *(*(new + j) + i))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

static void		tab_cpy(t_ull **dst, t_ull **src)
{
	int i;
	int j;

	j = 0;
	while (j < MAP_SIDE_SIZE)
	{
		i = 0;
		while (i < MAP_SIDE_SIZE)
		{
			*(*(dst + j) + i) = *(*(src + j) + i);
			i++;
		}
		j++;
	}
}

int				movement(t_ull **a, t_dir dir)
{
	int		i;
	t_ull	**new;
	int		ret;

	new = (t_ull**)malloc(sizeof(t_ull*) * (MAP_SIDE_SIZE + 1));
	i = 0;
	while (i < MAP_SIDE_SIZE + 1)
	{
		new[i] = (t_ull*)malloc(sizeof(t_ull) * (MAP_SIDE_SIZE + 1));
		i++;
	}
	tab_cpy(new, a);
	swipe(new, dir);
	ret = tab_cmp(a, new);
	i = 0;
	while (i < MAP_SIDE_SIZE + 1)
	{
		free(new[i]);
		i++;
	}
	free(new);
	return (ret);
}
