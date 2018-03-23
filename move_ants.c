/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:02:49 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/22 16:49:57 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		mover(t_lem *lem, int path, int ant)
{
	int inpt;
	int j;

	inpt = lem->route[path]->len - 1;
	while (inpt - 1 > 0)
	{
		lem->route[path]->route_map[inpt] = \
		lem->route[path]->route_map[inpt - 1];
		inpt--;
	}
	lem->route[path]->route_map[1] = ant;
	j = 1;
	while (j < lem->route[path]->len)
	{
		if (lem->route[path]->route_map[j] != 0)
			ft_printf("L%d-%s ", lem->route[path]->route_map[j], \
			lem->route[path]->room[j]);
		j++;
	}
	return (0);
}

static int		move_to_end(t_lem *lem, int path)
{
	int inpt;
	int j;

	inpt = lem->route[path]->len - 1;
	while (inpt - 1 > 0)
	{
		lem->route[path]->route_map[inpt] = \
		lem->route[path]->route_map[inpt - 1];
		inpt--;
	}
	lem->route[path]->route_map[1] = 0;
	j = 1;
	while (j < lem->route[path]->len)
	{
		if (lem->route[path]->route_map[j] != 0)
			ft_printf("L%d-%s ", lem->route[path]->route_map[j], \
			lem->route[path]->room[j]);
		j++;
	}
	return (0);
}

static void		move_to_end_wrapper(t_lem *lem, int *j, int i)
{
	move_to_end(lem, 0);
	(*j)++;
	i = -1;
	while (++i < lem->route[0]->len)
		if (lem->route[0]->route_map[i] != 0)
		{
			ft_printf("\n");
			break ;
		}
}

int				move_ants(t_lem *lem)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (!(lem->route[0]->route_map = (int *)malloc(sizeof(int) * \
	lem->route[0]->len)))
		return (1);
	ft_memset(lem->route[j]->route_map, 0, sizeof(int) * lem->route[0]->len);
	while (i <= lem->ant_qnt)
	{
		mover(lem, j, i);
		i++;
		ft_printf("\n");
	}
	j = 0;
	while (j <= lem->route[0]->len)
		move_to_end_wrapper(lem, &j, i);
	free(lem->route[0]->route_map);
	return (0);
}
