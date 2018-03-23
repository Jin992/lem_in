/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:38:52 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/21 20:11:05 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	link_add(t_lem *lem, t_room *add, int v, int i)
{
	struct s_room **tmp;

	tmp = NULL;
	if (!(tmp = (struct s_room**)malloc((sizeof(struct s_room*)) * \
	(lem->room[v]->link_qnt + 1))))
		return (1);
	tmp[lem->room[v]->link_qnt] = 0;
	while (lem->room[v]->link[++i] != 0)
		tmp[i] = lem->room[v]->link[i];
	free(lem->room[v]->link);
	if (!(lem->room[v]->link = \
	(struct s_room **)malloc((sizeof(struct s_room *)) * \
	(lem->room[v]->link_qnt + 1 + 1))))
		return (1);
	lem->room[v]->link[lem->room[v]->link_qnt + 1] = 0;
	i = -1;
	while (tmp[++i] != 0)
		lem->room[v]->link[i] = tmp[i];
	lem->room[v]->link[i] = add;
	lem->room[v]->link_qnt++;
	free(tmp);
	return (0);
}

int			link_realloc(t_lem *lem, t_room *add, int vertex, int i)
{
	if (lem->room[vertex]->link != NULL)
	{
		if (link_add(lem, add, vertex, i))
			return (1);
	}
	else
	{
		if (!(lem->room[vertex]->link = \
		(struct s_room **)malloc(sizeof(struct s_room *) * 2)))
			return (1);
		lem->room[vertex]->link[0] = add;
		lem->room[vertex]->link[1] = 0;
		lem->room[vertex]->link_qnt++;
	}
	return (0);
}

static int	room_add(t_lem *lem, t_room *add, t_room **tmp, int i)
{
	if (!(tmp = (t_room **)malloc((sizeof(t_room *)) * (lem->room_qnt + 1))))
		return (1);
	tmp[lem->room_qnt] = 0;
	while (lem->room[++i] != 0)
		tmp[i] = lem->room[i];
	free(lem->room);
	if (!(lem->room = (t_room **)malloc((sizeof(t_room *)) * \
	(lem->room_qnt + 1 + 1))))
		return (1);
	lem->room[lem->room_qnt + 1] = 0;
	i = -1;
	while (tmp[++i] != 0)
		lem->room[i] = tmp[i];
	lem->room[i] = add;
	free(tmp);
	return (0);
}

int			room_realloc(t_lem *lem, t_room *add)
{
	t_room	**tmp;
	int		i;

	i = -1;
	tmp = NULL;
	if (lem->room != NULL)
	{
		if (room_add(lem, add, tmp, i))
			return (1);
	}
	else
	{
		if (!(lem->room = (t_room **)malloc(sizeof(t_room *) * 2)))
			return (1);
		lem->room[1] = NULL;
		lem->room[0] = add;
	}
	return (0);
}
