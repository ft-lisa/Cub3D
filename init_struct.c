#include "cub3d.h"

t_element init_element(void)
{
    t_element element;

    element.c = 0;
    element.f = 0;
    element.no = 0;
    element.so = 0;
    element.ea = 0;
    element.we = 0;
    return(element);
}

t_data init_list(void)
{
    t_data texture;

    texture.map = NULL;
    texture.north = NULL;
    texture.south = NULL;
    texture.east = NULL;
    texture.west = NULL;
    texture.mlx = NULL;
    texture.win = NULL;
    texture.x = 0;
    texture.y = 0;
    return(texture);
}