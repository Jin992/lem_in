/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_links.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:45:38 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/16 20:45:46 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int check_room_eixst(int *i, t_lem *lem, char *res, int *room_exist)
{
    while (lem->room[*i] != 0)
    {
        if (ft_strcmp(res, lem->room[*i]->label) == 0)
        {
            (*room_exist)++;
            break;
        }
        (*i)++;
    }
    return (0);
}

int link_rooms(t_lem *lem, char **res, char **line)
{
    int room_exist = 0;
    int j;
    int i;

    j = 0;
    i = 0;
    if (lem->room == NULL)
        return (input_error(res));
    while (res[i] != 0)
        i++;
    if (i != 2)
        return (1);
    i = 0;
    lem->room_input = 1;
    check_room_eixst(&i, lem, res[0], &room_exist);
    check_room_eixst(&j, lem, res[1], &room_exist);
    if (room_exist != 2)
        return (input_error(res));
    write_to_map(lem, line);
    link_realloc(lem, lem->room[i], j, -1);
    link_realloc(lem, lem->room[j], i, -1);
    lem->links += 2;
    return (0);
}
