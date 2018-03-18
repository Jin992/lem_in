/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_room_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:42:13 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/18 17:49:26 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_room *room_init(char **res)
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


