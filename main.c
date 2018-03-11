
#include <stdio.h>
#include <stdlib.h>

#define INF 2147483647

typedef  struct s_room
{
    int             room_id;
    char            *label;
    struct s_room   **link;
    int             distance;
    int             mark;
}               t_room;

typedef struct  s_lem
{
    int     ant_qnt;
    int     room_qnt;
    t_room  **room;
    t_room  *start;
    t_room  *end;
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

int lead_ants(t_lem *data)
{

}

int main()
{
    t_lem lemin;

    lemin.distance = 0;

    lemin.ant_qnt = 3;
    lemin.room_qnt = 4;
    lemin.room = (t_room **)malloc(sizeof(t_room *) * (lemin.room_qnt + 1));
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

    lemin.room[0]->room_id = 0;
    lemin.room[1]->room_id = 1;
    lemin.room[2]->room_id = 2;
    lemin.room[3]->room_id = 3;

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
    printf("\n");
    find_route(lemin.end, &lemin);
    while (lemin.room[i] != 0)
        printf("elem %d distance : %d\n", i, lemin.room[i++]->distance);
    return (0);
}