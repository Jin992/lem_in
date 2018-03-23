/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:44:31 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/22 16:28:27 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			input_error(char **res)
{
	if (res != 0)
	{
		if (res[0] == '\0')
			free(res);
		else
			ft_free_str_arr(res);
	}
	return (1);
}

int			check_digit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		if (!ft_isdigit(str[i++]))
			return (1);
	return (0);
}

static int	room_and_links(char **res, char **line, int i, t_lem *lem)
{
	if (!(res = ft_strsplit(*line, '-')))
		return (1);
	if (res[0] == NULL)
		return (input_error(res));
	while (res[i] != 0)
		i++;
	if (i == 2)
	{
		if (link_rooms(lem, res, line))
		{
			ft_strdel(line);
			return (input_error(res));
		}
	}
	else if (lem->room_input == 1)
		return (input_error(res));
	if (lem->room_input == 0)
	{
		if (check_rooms(line, lem))
			return (input_error(res));
	}
	ft_free_str_arr(res);
	return (0);
}

static int	check_map(t_lem *lem, char **line, int i)
{
	char **res;

	res = NULL;
	if (lem->ant_qnt == 0)
	{
		if (check_ants(*line, lem))
			return (-1);
	}
	else
	{
		if (room_and_links(res, line, i, lem))
			return (1);
	}
	return (0);
}

int			validation(t_lem *lem)
{
	char	*line;
	int		end;

	line = NULL;
	while ((end = get_next_line(0, &line)) > 0)
	{
		if (line[0] == '#' && ft_strcmp(line, "##start") != 0
			&& ft_strcmp(line, "##end") != 0)
		{
			write_to_map(lem, &line);
			ft_strdel(&line);
			continue ;
		}
		if (check_map(lem, &line, 0))
			return (free_line(&line));
		ft_strdel(&line);
	}
	if (end == 0)
		return (free_line(&line));
	if (end == -1)
		return (1);
	ft_strdel(&line);
	return (0);
}
