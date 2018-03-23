/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_route_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:49:54 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/21 20:01:15 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		swap_route(t_lem *lem, int elem1, int elem2, int *swap)
{
	t_route	*tmp;

	tmp = lem->route[elem1];
	lem->route[elem1] = lem->route[elem2];
	lem->route[elem2] = tmp;
	*swap = 1;
}

t_route		*make_new_route(t_lem *lem, int i, char *end)
{
	t_route	*new_route;
	char	*sep_tmp;
	int		j;

	if (!(new_route = (t_route *)malloc(sizeof(t_route))))
		return (NULL);
	sep_tmp = lem->separate_routes[i];
	if (!(lem->separate_routes[i] = ft_strjoin(lem->separate_routes[i], end)))
		return (NULL);
	free(sep_tmp);
	if (!(new_route->room = ft_strsplit(lem->separate_routes[i], ' ')))
		return (NULL);
	j = 0;
	while (new_route->room[j] != 0)
		j++;
	new_route->len = j;
	return (new_route);
}

static int	route_add(t_lem *lem, t_route *add, t_route **tmp, int i)
{
	if (!(tmp = (t_route **)malloc((sizeof(t_route *)) * (lem->route_qnt + 1))))
		return (1);
	tmp[lem->route_qnt] = 0;
	while (lem->route[++i] != 0)
		tmp[i] = lem->route[i];
	free(lem->route);
	if (!(lem->route = (t_route **)malloc((sizeof(t_route *)) * \
	(lem->route_qnt + 1 + 1))))
		return (1);
	lem->route[lem->route_qnt + 1] = 0;
	i = -1;
	while (tmp[++i] != 0)
		lem->route[i] = tmp[i];
	lem->route[i] = add;
	free(tmp);
	return (0);
}

int			route_realloc(t_lem *lem, t_route *add)
{
	t_route	**tmp;
	int		i;

	i = -1;
	tmp = NULL;
	if (lem->route != NULL)
	{
		if (route_add(lem, add, tmp, i))
			return (1);
	}
	else
	{
		if (!(lem->route = (t_route **)malloc(sizeof(t_route *) * 2)))
			return (1);
		lem->route[1] = NULL;
		lem->route[0] = add;
	}
	return (0);
}
