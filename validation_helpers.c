/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_helpers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 19:10:10 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/21 19:18:39 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		write_to_map(t_lem *lem, char **line)
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

int		free_line(char **line)
{
	ft_strdel(line);
	return (1);
}
