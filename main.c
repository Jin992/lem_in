
#include <stdio.h>
#include "lem_in.h"



void lemin_init(t_lem *lemin)
{
    lemin->distance = 0;
    lemin->ant_qnt = 0;
    lemin->start = NULL;
    lemin->end = NULL;
    lemin->links = NULL;
    lemin->room_qnt = 0;
    lemin->start_flag = 0;
    lemin->end_flag = 0;
    lemin->room = NULL;
    lemin->room_input = 0;
    lemin->route = NULL;
	lemin->route_qnt = 0;
}

int    compose_route(t_lem *lem, char *line, char *delim)
{
    char *tmp;

    tmp = lem->routes;
    if (tmp != NULL && tmp[0] == '\0')
        delim = "";
    lem->routes = ft_strjoin(lem->routes, delim);
    if (tmp != NULL)
        free(tmp);
    tmp = lem->routes;
    lem->routes = ft_strjoin(lem->routes,line) ;
    free(tmp);
    return (0);
}


int lead_ants(t_room **room, t_lem *lem)
{
    int i;

    if (*room == lem->end)
        return (0);
    i = 0;
    if ((*room)->link == NULL)
        return (1);
    if ((*room)->link[i] != 0)
    {
        while ((*room)->link[i] != 0)
        {
            if ((*room)->link[i]->distance < (*room)->distance)
            {
                ft_printf("Name %s distance :%d\n", (*room)->label, (*room)->distance);
                if (ft_strcmp((*room)->label, lem->start->label) == 0)
                    compose_route(lem, (*room)->label, "\t");
                else
                    compose_route(lem, (*room)->label, " ");
                lead_ants(&(*room)->link[i], lem);
            }
            i++;
        }
    }
    return (0);
}


int make_routes(t_lem *lem)
{
    int i;
    int routes;
    int j;
    t_route *new_route;

    i = 0;
    j = 0;
    routes = 1;
    while (lem->routes[i] != '\0')
        if (lem->routes[i++] == '\t')
            routes++;
    lem->separate_routes = ft_strsplit(lem->routes, '\t');
    ft_printf("Routes qnt : %d\n", routes);
    i = 0;
    while (i < routes)
        ft_printf("%s\n",lem->separate_routes[i++]);

    i = 0;
    lem->original_routes = (char ***)malloc(sizeof(char **) * (routes + 1));
    lem->original_routes[routes] = 0;
    while (i < routes)
    {
        new_route = (t_route *)malloc(sizeof(t_route));
        new_route->room = ft_strsplit(lem->separate_routes[i], ' ');
        j = 0;
        while (new_route->room[j] != 0)
            j++;
        new_route->len = j;
        route_realloc(lem, new_route);
        lem->route_qnt++;
        i++;
    }
    i = 0;
    while (lem->route[i] != 0)
    {
        ft_printf("%d : \n", i);
        j = 0;
        while (lem->route[i]->room[j] != 0)
            ft_printf("%s\n", lem->route[i]->room[j++]);
		i++;
    }
    return (0);
}

int move_ants(t_lem *lem)
{
	int i;
	int j;
	int route_len;
	int input = 0;

	route_len = lem->route[0]->len;
	lem->route[0]->route_map = (int *)malloc(sizeof(int) * route_len);
	ft_memset(lem->route[0]->route_map, 0, sizeof(int) * route_len);
	while (lem->ant_qnt + lem->route[0]->len > 0)
	{
		i = 0;
		while (i < lem->route[0]->len)
		{
			if (lem->route[0]->route_map[0] == 0 && lem->ant_qnt > 0)
			{
				lem->route[0]->route_map[0] = 1;
			}
			else
			{
				if (lem->route[0]->route_map[i] > 0)
					lem->route[0]->route_map[i]++;
				if (i + 1 <  lem->route[0]->len)
					if (lem->route[0]->route_map[i] > 0 && lem->route[0]->route_map[i + 1] == 0)
					{
						lem->route[0]->route_map[i + 1] = 1;
						input = 1;
					}
			}
			if (input == 1)
			{
				input = 0;
				break ;
			}
			i++;
			ft_printf("___________________________________\n");
		}
		j = 0;
		while (j < lem->route[0]->len)
		{
			ft_printf("%d ", lem->route[0]->route_map[j]);
			j++;
		}
		ft_printf("\n");

		if (lem->ant_qnt > 0)
			lem->ant_qnt--;
		if (lem->ant_qnt == 0)
			route_len--;
	}
}


int main()
{
   t_lem lemin;
   int i;

   i = 0;
   lemin_init(&lemin);
   if (validation(&lemin))
   {
        if (lemin.ant_qnt == 0)
            return ((int)write(1,"ERROR\n", 6));
       if (lemin.room == NULL)
           return ((int)write(1,"ERROR\n", 6));
       if (lemin.start == NULL || lemin.end == NULL || lemin.start_flag != 1 || lemin.end_flag != 1)
           return ((int)write(1,"ERROR\n", 6));
       if (lemin.links == 0)
           return ((int)write(1,"ERROR\n", 6));
       if (lemin.start->link != NULL && lemin.end->link != NULL)
        find_route(&lemin.end, &lemin);
       else
           return ((int)write(1,"ERROR5\n", 7));
       if (lemin.start->link == NULL)
           return ((int)write(1,"ERROR\n", 6));
       while (lemin.start->link[i] != 0)
       {
           if (lemin.start->link[i]->distance != INF)
               break;
           i++;
       }
       if (lemin.start->link[i] == NULL)
           return ((int)write(1,"ERROR1\n", 7));
   }
    ft_printf("%s\n", lemin.map_data);
    i = 0;

    if (lemin.room != NULL)
        while (lemin.room[i] != 0)
            printf("elem %d distance : %d\n", i, lemin.room[i++]->distance);
    lemin.routes = ft_strdup("");
    lead_ants(&lemin.start, &lemin);
    make_routes(&lemin);
    ft_printf("%s\n", lemin.routes);
	move_ants(&lemin);
    return (0);
}