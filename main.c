
#include <stdio.h>
#include "lib/includes/libft.h"
#include "lib/includes/ft_printf.h"
#include <stdlib.h>

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

typedef struct  s_lem
{
    int     ant_qnt;
    int     room_qnt;
    t_room  **room;
    t_room  *start;
    t_room  *end;
    int     room_input;
    int     distance;

}               t_lem;


int reset(t_room *data, t_lem *lem)
{
    data->mark = 0;
    lem->distance--;
    return (0);

}

int find_route(t_room *data, t_lem *lem)
{
    int i;

    if (data == lem->start)
        return (0);
    i = 0;
    if (data != lem->end)
    {
        data->mark = 1;
        data->distance = ++(lem->distance);
    }
    if (data->link[i] != 0)
        while (data->link[i] != 0)
        {
            if ((((data->link)[i])->mark || (data->link)[i]->distance <= data->distance) && ++i)
                continue ;
            find_route(data->link[i], lem);
            ++i;
        }
    reset(data, lem);
    return (0);
}

int input_error(char **res)
{
    ft_free_str_arr(res);
    write(1, "ERROR\n", 6);
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

int check_ants(char *line, t_lem *lem)
{
    char **res;

    res = ft_strsplit(line, ' ');
    if (res[1] == NULL && ft_isdigit(res[0][0]))
    {
        if (check_digit(res[0]))
            return (input_error(res));
        lem->ant_qnt = (int) ft_atoi(res[0]);
        ft_free_str_arr(res);
        ft_putstr(line);
        ft_putstr("\n");
    }
    else
        return (input_error(res));
    return (0);
}


int room_realloc(t_lem *lem, t_room *add)
{
    t_room **tmp;
    int i;

    i = -1;
    if (lem->room != NULL)
    {
        tmp = (t_room **)malloc((sizeof(t_room *)) * (lem->room_qnt + 1));
        tmp[lem->room_qnt] = 0;
        while (lem->room[++i] != 0)
            tmp[i] = lem->room[i];
        lem->room = (t_room **)malloc((sizeof(t_room *)) * (lem->room_qnt + 1 + 1));
        lem->room[lem->room_qnt + 1] = 0;
        i = -1;
        while (tmp[++i] != 0)
            lem->room[i] = tmp[i];
        lem->room[i] = add;
        free(tmp);
    }
    else
    {
        lem->room = (t_room **)malloc(sizeof(t_room *) * 2);
        lem->room[1] = 0;
        lem->room[0] = add;
    }
    return (0);
}

int check_rooms(char **line, t_lem *lem)
{
    char **res;
    int i;
    int start_flag;
    int end_flag;

    start_flag = 0;
    end_flag = 0;
    i = 0;
    res = ft_strsplit(*line, ' ');
    if (res[1] == 0 && (ft_strcmp(res[0], "##start") == 0 || ft_strcmp(res[0], "##end") == 0))
    {
        if (ft_strcmp(res[0], "##start") == 0)
        {
            ft_free_str_arr(res);
            free(*line);
            while (get_next_line(0, line) == 1)
            {
                if ((*line)[0] != '#')
                    break;
                free (*line);
            }
            ft_putstr("start\n");
            res = ft_strsplit(*line, ' ');
            start_flag = 1;

        }
        if (ft_strcmp(res[0], "##end") == 0)
        {
            ft_free_str_arr(res);
            free(*line);
            while (get_next_line(0, line) == 1)
            {
                if ((*line)[0] != '#')
                    break;
                free (*line);
            }
            ft_putstr("end\n");
            res = ft_strsplit(*line, ' ');
            end_flag = 1;
        }
    }
    while (res[i] != 0)
        i++;
    if (i != 3 || check_digit(res[1]) || check_digit(res[2]))
        return (input_error(res));
    t_room *new_room;
    new_room = (t_room *)malloc(sizeof(t_room) * 1);
    new_room->label = ft_strdup(res[0]);
    new_room->x = (int)ft_atoi(res[1]);
    new_room->y = (int)ft_atoi(res[2]);
    new_room->link = 0;
    ft_printf("Label: %s x: %d y: %d\n", new_room->label, new_room->x, new_room->y);
    room_realloc(lem, new_room);
    if (lem->start == NULL && start_flag == 1)
    {
        lem->start = new_room;
        ft_printf("start room label %s\n", lem->start->label );
    }
    if (lem->end == NULL && end_flag == 1)
    {
        lem->end = new_room;
        ft_printf("end room label %s\n", lem->end->label );
    }
    i = 0;
    while (lem->room[i] != 0)
        printf("label %s \n", lem->room[i++]->label);
    lem->room_qnt++;
    return (0);
}



int link_realloc(t_lem *lem, t_room *add, int vertex)
{
    struct s_room **tmp;
    int i;

    i = -1;
    if (lem->room[vertex]->link != NULL)
    {
        tmp = (struct s_room**)malloc((sizeof(struct s_room*)) * (lem->room[vertex]->link_qnt + 1));
        tmp[lem->room[vertex]->link_qnt] = 0;
        while (lem->room[vertex]->link[++i] != 0)
            tmp[i] = lem->room[vertex]->link[i];
        lem->room[vertex]->link = (struct s_room **)malloc((sizeof(struct s_room*)) * (lem->room[vertex]->link_qnt + 1 + 1));
        lem->room[vertex]->link[lem->room[vertex]->link_qnt + 1] = 0;
        i = -1;
        while (tmp[++i] != 0)
            lem->room[vertex]->link[i] = tmp[i];
        lem->room[vertex]->link[i] = add;
        free(tmp);
    }
    else
    {
        lem->room[vertex]->link = (struct s_room **)malloc(sizeof(struct s_room *) * 2);
        lem->room[vertex]->link[1] = 0;
        lem->room[vertex]->link[0] = add;
    }
    return (0);
}

int validation(t_lem *lem)
{
    char *line;
    int i;

    i = 0;
    char **res;
    lem->ant_qnt = 0;
    lem->room_input = 0;
    while (get_next_line(0, &line) == 1)
    {
        if (line[0] == '#' && ft_strcmp(line, "##start") != 0 && ft_strcmp(line, "##end") != 0)
        {
            free(line);
            continue ;
        }
        if (lem->ant_qnt == 0)
        {
            if (check_ants(line, lem))
                return (-1);
        }
        else
        {
            i = 0;
            res = ft_strsplit(line, '-');
            while (res[i] != 0)
                i++;
            if (i == 2)
            {
                    lem->room_input = 1;
                    link_realloc(lem, lem->room[0], 1);
                    link_realloc(lem, lem->room[1], 0);
                    ft_printf("rooms end\n");
            }
            if (lem->room_input == 0)
            {
                if (check_rooms(&line, lem))
                    return (-1);
            }
        }
        free (line);
    }
}

int main()
{
    t_lem lemin;

   lemin.distance = 0;

    lemin.ant_qnt = 3;
    //lemin.room_qnt = 4;
    lemin.start = NULL;
    lemin.end = NULL;

   /* lemin.room = (t_room **)malloc(sizeof(t_room*) * (lemin.room_qnt + 1));
    lemin.room[lemin.room_qnt] = 0;
    lemin.room[0] = (t_room *)malloc(sizeof(t_room));
    lemin.room[1] = (t_room *)malloc(sizeof(t_room));
    lemin.room[2] = (t_room *)malloc(sizeof(t_room));
    lemin.room[3] = (t_room *)malloc(sizeof(t_room));

    lemin.room[0]->mark = 0;
    lemin.room[1]->mark = 0;
    lemin.room[2]->mark = 0;
    lemin.room[3]->mark = 0;

    lemin.room[0]->distance = INF;
    lemin.room[1]->distance = 0;
    lemin.room[2]->distance = INF;
    lemin.room[3]->distance = INF;


    lemin.room[0]->label = "0";
    lemin.room[1]->label = "1";
    lemin.room[2]->label = "2";
    lemin.room[3]->label = "3";

    lemin.room[0]->link = (struct s_room **)malloc(sizeof(struct s_room *) * (2 + 1));
    lemin.room[0]->link[2] = 0;
    lemin.room[0]->link[0] = lemin.room[2];
    lemin.room[0]->link[1] = lemin.room[3];

    lemin.room[1]->link = (struct s_room **)malloc(sizeof(struct s_room *) * (2 + 1));
    lemin.room[1]->link[0] = lemin.room[2];
    lemin.room[1]->link[1] = lemin.room[3];
    lemin.room[1]->link[2] = NULL;

    lemin.room[2]->link = (struct s_room **)malloc(sizeof(struct s_room *) * (3 + 1));
    lemin.room[2]->link[3] = 0;
    lemin.room[2]->link[0] = lemin.room[0];
    lemin.room[2]->link[1] = lemin.room[1];
    lemin.room[2]->link[2] = lemin.room[3];

    lemin.room[3]->link = (struct s_room **)malloc(sizeof(struct s_room *) * (3 + 1));
    lemin.room[3]->link[3] = 0;
    lemin.room[3]->link[0] = lemin.room[1];
    lemin.room[3]->link[1] = lemin.room[0];
    lemin.room[3]->link[2] = lemin.room[2];

    lemin.start = lemin.room[0];
    lemin.end = lemin.room[1];

    int i = 0;
    while (lemin.room[i] != 0)
        printf("distance : %d\n", lemin.room[i++]->distance);
    i = 0;
    printf("\n");*/
    int i = 0;
    //find_route(lemin.end, &lemin);
    //while (lemin.room[i] != 0)
      //  printf("elem %d distance : %d\n", i, lemin.room[i++]->distance);
    validation(&lemin);
    while (lemin.room[i] != 0)
        printf("elem %d distance : %d\n", i, lemin.room[i++]->distance);
    return (0);
}