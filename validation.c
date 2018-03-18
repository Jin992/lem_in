/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:44:31 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/18 15:15:32 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int input_error(char **res)
{
    ft_free_str_arr(res);
    return (1);
}

int check_digit(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
        if (!ft_isdigit(str[i++]))
            return (1);
    return (0);
}

int    write_to_map(t_lem *lem, char **line)
{
    char *tmp;

    tmp = lem->map_data;
    lem->map_data = ft_strjoin(lem->map_data, *line);
    free(tmp);
    tmp = lem->map_data;
    lem->map_data = ft_strjoin(lem->map_data, "\n");
    free(tmp);
    return (0);
}

static int check_map(t_lem *lem, char **res, char **line, int i)
{
    if (lem->ant_qnt == 0)
    {
        if (check_ants(*line, lem))
            return (-1);
    }
    else
    {
        res = ft_strsplit(*line, '-');
        if (res == NULL || res[0] == NULL)
            return (1);
        while (res[i] != 0)
            i++;
        if (i == 2)
        {
            if (link_rooms(lem, res, line))
                return (1);
        }
        else if (lem->room_input == 1)
            return (1);
        if (lem->room_input == 0)
        {
            if (check_rooms(line, lem))
                return (1);
        }
    }
    return (0);
}


int validation(t_lem *lem)
{
    char *line;
    char **res;
    int    end;

    res = NULL;
    while ((end = get_next_line(0, &line)) == 1)
    {
        if (line[0] == '#' && ft_strcmp(line, "##start") != 0 && ft_strcmp(line, "##end") != 0)
        {
            write_to_map(lem, &line);
            free(line);
            continue ;
        }
        if (check_map(lem, res, &line, 0))
            return (1);
        free (line);
    }
    if (end == 0)
        return (1);
    return (0);
}

