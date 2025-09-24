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
	texture.color_ceilling = -1;
	texture.color_floor = -1;
    texture.x = 0;
    texture.y = 0;
    texture.angle = (PI);
	//
	texture.w = 0;
	texture.s = 0;
	texture.a = 0;
	texture.d = 0;
	texture.left = 0;
	texture.right = 0;
    return(texture);
}
