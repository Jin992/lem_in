/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:48:36 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/18 12:39:45 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int	reset(t_room **data, t_lem *lem)
{
	(*data)->mark = 0;
	lem->distance--;
	return (0);
}

int			find_route(t_room **data, t_lem *lem)
{
	int i;

	if (*data == lem->start)
		return (0);
	i = 0;
	if (*data != lem->end)
	{
		(*data)->mark = 1;
		(*data)->distance = ++(lem->distance);
	}
	if ((*data)->link == NULL)
		return (1);
	if ((*data)->link[i] != 0)
		while ((*data)->link[i] != 0)
		{
			if (((*data)->link)[i] == NULL)
				return (0);
			if (((((*data)->link)[i])->mark ||
					((*data)->link)[i]->distance <= (*data)->distance) && ++i)
				continue ;
			find_route(&((*data)->link[i]), lem);
			++i;
		}
	reset(data, lem);
	return (0);
}
