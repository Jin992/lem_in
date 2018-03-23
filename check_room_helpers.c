/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_room_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:42:13 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/21 18:26:14 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room	*room_init(char **res)
{
	t_room *tmp;

	tmp = (t_room *)malloc(sizeof(t_room) * 1);
	tmp->label = ft_strdup(res[0]);
	tmp->x = (int)ft_atoi(res[1]);
	tmp->y = (int)ft_atoi(res[2]);
	tmp->link = NULL;
	tmp->distance = INF;
	tmp->mark = 0;
	tmp->link = 0;
	tmp->link_qnt = 0;
	return (tmp);
}

int		room_to_add(t_lem *lem, char **line, char **res)
{
	t_room *new_room;

	new_room = room_init(res);
	write_to_map(lem, line);
	room_realloc(lem, new_room);
	if (lem->start == NULL && lem->start_flag == 1)
		lem->start = new_room;
	if (lem->end == NULL && lem->end_flag == 1)
	{
		lem->end = new_room;
		lem->end->link_qnt = 0;
		lem->end->distance = 0;
	}
	return (0);
}
