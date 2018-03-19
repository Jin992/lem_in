/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: earteshc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/16 17:04:10 by earteshc          #+#    #+#             */
/*   Updated: 2018/03/18 19:51:40 by jdoeeshc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
#define LEM_IN_H
#include "lib/includes/libft.h"
#include "lib/includes/ft_printf.h"

#define INF 2147483647

typedef  struct s_room
{
    char            *label;
    struct s_room   **link;
    int             distance;
    int             x;
    int             y;
    int             mark;
    int             link_qnt;
}               t_room;

typedef struct s_route
{
	char	**room;
	int		len;
	int 	*route_map;
}				t_route;

typedef struct  s_lem
{
    int     ant_qnt;
    int     room_qnt;
    t_room  **room;
    t_room  *start;
    t_room  *end;
    int     room_input;
    int     distance;
    int     links;
    char    *map_data;
    int     start_flag;
    int     end_flag;
    char    *routes;
    char    **separate_routes;
    char    ***original_routes;
	t_route	**route;
	int 	route_qnt;

}               t_lem;

int             link_realloc(t_lem *lem, t_room *add, int vertex, int i);
int room_realloc(t_lem *lem, t_room *add);
t_room *room_init(char **res);
int check_rooms(char **line, t_lem *lem);
int    write_to_map(t_lem *lem, char **line);
int check_digit(char *str);
int input_error(char **res);
int validation(t_lem *lem);
int link_rooms(t_lem *lem, char **res, char **line);
int find_route(t_room **data, t_lem *lem);
int check_ants(char *line, t_lem *lem);
int route_realloc(t_lem *lem, t_route *add);
#endif
