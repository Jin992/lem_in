/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_route.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:25:33 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/21 19:59:13 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			compose_route(t_lem *lem, char *line, char *delim)
{
	char *tmp;

	tmp = lem->routes;
	if (tmp != NULL && tmp[0] == '\0')
		delim = "";
	lem->routes = ft_strjoin(lem->routes, delim);
	if (tmp != NULL)
		free(tmp);
	tmp = lem->routes;
	lem->routes = ft_strjoin(lem->routes, line);
	free(tmp);
	return (0);
}

int			sort_routes(t_lem *lem)
{
	int		i;
	int		swap;

	i = 0;
	swap = 0;
	while (lem->route[i] != 0)
	{
		if (lem->route[i + 1] != 0)
			if (lem->route[i]->len > lem->route[i + 1]->len)
				swap_route(lem, i, i + 1, &swap);
		if (swap != 0)
		{
			swap = 0;
			i = 0;
		}
		else
			i++;
	}
	return (0);
}

int			lead_ants(t_room **room, t_lem *lem)
{
	int i;

	if (*room == lem->end)
		return (0);
	i = 0;
	if ((*room)->link == NULL)
		return (1);
	if ((*room)->link[i] != 0)
	{
		while ((*room)->link[i] != 0)
		{
			if ((*room)->link[i]->distance < (*room)->distance)
			{
				if (ft_strcmp((*room)->label, lem->start->label) == 0)
					compose_route(lem, (*room)->label, "\t");
				else
					compose_route(lem, (*room)->label, " ");
				lead_ants(&(*room)->link[i], lem);
			}
			i++;
		}
	}
	return (0);
}

int			make_routes(t_lem *lem)
{
	int			i;
	int			routes;
	t_route		*new_route;
	char		*end;

	i = 0;
	routes = 1;
	end = ft_strjoin(" ", lem->end->label);
	while (lem->routes[i] != '\0')
		if (lem->routes[i++] == '\t')
			routes++;
	lem->separate_routes = ft_strsplit(lem->routes, '\t');
	i = 0;
	while (i < routes)
	{
		if (!(new_route = make_new_route(lem, i, end)))
			return (1);
		route_realloc(lem, new_route);
		lem->route_qnt++;
		i++;
	}
	ft_free_str_arr(lem->separate_routes);
	free(end);
	sort_routes(lem);
	return (0);
}
