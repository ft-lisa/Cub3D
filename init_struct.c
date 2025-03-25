#include "err_mess.h"
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