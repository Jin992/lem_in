/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:03:32 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/22 16:49:57 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		check_start(char **line, char ***res, t_lem *lem)
{
	if (ft_strcmp((*res)[0], "##start") == 0)
	{
		write_to_map(lem, line);
		ft_free_str_arr(*res);
		free(*line);
		*line = NULL;
		while (get_next_line(0, line) == 1)
		{
			if ((*line)[0] != '#')
				break ;
			free(*line);
			*line = NULL;
		}
		*res = ft_strsplit(*line, ' ');
		lem->start_flag++;
	}
	return (0);
}

static int		check_end(char **line, char ***res, t_lem *lem)
{
	if (ft_strcmp((*res)[0], "##end") == 0)
	{
		write_to_map(lem, line);
		ft_free_str_arr(*res);
		free(*line);
		*line = NULL;
		while (get_next_line(0, line) == 1)
		{
			if ((*line)[0] != '#')
				break ;
			write_to_map(lem, line);
			free(*line);
			*line = NULL;
		}
		*res = ft_strsplit(*line, ' ');
		lem->end_flag++;
	}
	return (0);
}

static int		check_for_duplicity(t_lem *lem, char **res)
{
	int i;

	i = 0;
	while (lem->room != NULL && lem->room[i] != 0)
	{
		if (ft_atoi(res[1]) == lem->room[i]->x && ft_atoi(res[2]) == \
		lem->room[i]->y)
			return (input_error(res));
		if (ft_strcmp((res)[0], lem->room[i++]->label) == 0)
			return (input_error(res));
	}
	return (0);
}

static int		check_room_data_composition(char **res)
{
	int i;

	i = 0;
	while (res[i] != 0)
		i++;
	if (i != 3 || check_digit(res[1]) || check_digit(res[2]))
		return (input_error(res));
	return (0);
}

int				check_rooms(char **line, t_lem *lem)
{
	char **res;

	res = ft_strsplit(*line, ' ');
	if (res == NULL || res[0] == NULL)
		return (1);
	if (res[1] == 0 && ft_strcmp(res[0], "##start") == 0)
		check_start(line, &res, lem);
	if (res == NULL || res[0] == NULL)
		return (1);
	if (res[1] == 0 && ft_strcmp(res[0], "##end") == 0)
		check_end(line, &res, lem);
	if (res == NULL || res[0] == NULL)
		return (1);
	if (res[0][0] == 'L')
		return (input_error(res));
	if (check_room_data_composition(res))
		return (1);
	if (check_for_duplicity(lem, res))
		return (1);
	room_to_add(lem, line, res);
	lem->room_qnt++;
	if (res != NULL)
		ft_free_str_arr(res);
	return (0);
}
