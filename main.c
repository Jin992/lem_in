
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
    lemin->routes = NULL;
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
        lem->original_routes[i] = ft_strsplit(lem->separate_routes[i], ' ');
        i++;
    }
    i = 0;
    while (lem->original_routes[i] != 0)
    {
        ft_printf("%d : \n", i);
        j = 0;
        while (lem->original_routes[i][j] != 0)
            ft_printf("%s\n", lem->original_routes[i][j++]);
        i++;
    }
    return (0);
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
    return (0);
}