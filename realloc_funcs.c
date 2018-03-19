/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc_funcs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:38:52 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/18 12:55:24 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int link_add(t_lem *lem, t_room *add, int v, int i, struct s_room **tmp)
{
    if (!(tmp = (struct s_room**)malloc((sizeof(struct s_room*)) * \
    (lem->room[v]->link_qnt + 1))))
        return (1);
    tmp[lem->room[v]->link_qnt] = 0;
    while (lem->room[v]->link[++i] != 0)
        tmp[i] = lem->room[v]->link[i];
    if (!(lem->room[v]->link = \
    (struct s_room **)malloc((sizeof(struct s_room*)) * \
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

int link_realloc(t_lem *lem, t_room *add, int vertex, int i)
{
    struct s_room **tmp;

    tmp = NULL;
    if (lem->room[vertex]->link != NULL)
    {
        if (link_add(lem, add, vertex, i, tmp))
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

static int room_add(t_lem *lem, t_room *add, t_room **tmp, int i)
{
    if (!(tmp = (t_room **)malloc((sizeof(t_room *)) * (lem->room_qnt + 1))))
        return (1);
    tmp[lem->room_qnt] = 0;
    while (lem->room[++i] != 0)
        tmp[i] = lem->room[i];
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

int room_realloc(t_lem *lem, t_room *add)
{
    t_room **tmp;
    int i;

    i = -1;
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

static int route_add(t_lem *lem, t_route *add, t_route **tmp, int i)
{
    if (!(tmp = (t_route **)malloc((sizeof(t_route *)) * (lem->route_qnt + 1))))
        return (1);
    tmp[lem->route_qnt] = 0;
    while (lem->route[++i] != 0)
        tmp[i] = lem->route[i];
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

int route_realloc(t_lem *lem, t_route *add)
{
    t_route **tmp;
    int i;

    i = -1;
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