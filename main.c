/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 20:22:32 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/22 16:49:57 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "lem_in.h"

void		lemin_init(t_lem *lemin)
{
	lemin->distance = 0;
	lemin->ant_qnt = 0;
	lemin->start = NULL;
	lemin->end = NULL;
	lemin->links = 0;
	lemin->room_qnt = 0;
	lemin->start_flag = 0;
	lemin->end_flag = 0;
	lemin->room = NULL;
	lemin->room_input = 0;
	lemin->route = NULL;
	lemin->route_qnt = 0;
}

int			exit_error(t_lem *lem)
{
	free_lem(lem);
	write(1, "ERROR\n", 6);
	return (1);
}

static int	validate(t_lem *lemin)
{
	if (lemin->ant_qnt == 0)
		return (exit_error(lemin));
	if (lemin->room == NULL)
		return (exit_error(lemin));
	if (lemin->start == NULL || lemin->end == NULL
		|| lemin->start_flag != 1 || lemin->end_flag != 1)
		return (exit_error(lemin));
	if (lemin->links == 0)
		return (exit_error(lemin));
	if (lemin->start->link != NULL && lemin->end->link != NULL)
		find_route(&lemin->end, lemin);
	else
		return (exit_error(lemin));
	if (lemin->start->link == NULL)
		return (exit_error(lemin));
	return (0);
}

int			main(void)
{
	t_lem	lemin;
	int		i;

	i = -1;
	lemin_init(&lemin);
	if (validation(&lemin))
	{
		if (validate(&lemin))
			return (1);
		while (lemin.start->link[++i] != 0)
			if (lemin.start->link[i]->distance != INF)
				break ;
		if (lemin.start->link[i] == NULL)
			return (exit_error(&lemin));
	}
	if (!(lemin.routes = ft_strdup("")))
		return (free_lem(&lemin));
	ft_printf("%s\n", lemin.map_data);
	lead_ants(&lemin.start, &lemin);
	make_routes(&lemin);
	move_ants(&lemin);
	free_lem(&lemin);
	return (0);
}
