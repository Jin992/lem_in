/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:12:10 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/21 20:14:02 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void		free_rooms(t_lem *lem)
{
	int i;

	i = 0;
	if (lem->room == NULL)
		return ;
	while (lem->room[i] != 0)
	{
		if (lem->room[i]->label != NULL)
			free(lem->room[i]->label);
		if (lem->room[i]->link != NULL)
			free(lem->room[i]->link);
		free(lem->room[i]);
		i++;
	}
	if (lem->room != NULL)
		free(lem->room);
}

static void		free_routes(t_lem *lem)
{
	int i;

	i = 0;
	if (lem->route == NULL)
		return ;
	while (lem->route[i] != 0)
	{
		ft_free_str_arr(lem->route[i]->room);
		free(lem->route[i]);
		i++;
	}
	free(lem->route[i]);
	free(lem->route);
}

int				free_lem(t_lem *lem)
{
	if (lem->map_data != NULL)
		free(lem->map_data);
	if (lem->routes != NULL)
		free(lem->routes);
	free_rooms(lem);
	free_routes(lem);
	return (1);
}
