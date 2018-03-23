/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_ants.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:49:37 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/22 16:49:57 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int	check_ants(char *line, t_lem *lem)
{
	char **res;

	res = ft_strsplit(line, ' ');
	if (res[0] == NULL)
		return (input_error(res));
	if (res[1] == NULL && ft_isdigit(res[0][0]))
	{
		if (check_digit(res[0]))
			return (input_error(res));
		lem->ant_qnt = (int)ft_atoi(res[0]);
		ft_free_str_arr(res);
		lem->map_data = ft_strjoin(line, "\n");
	}
	else
		return (input_error(res));
	return (0);
}
