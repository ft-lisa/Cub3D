#include "cub3d.h"


int     main(int argc, char** argv)
{
        t_data texture;
        if (argc != 2)
                return(printf(ERR_ARG), EXIT_FAILURE);
        if (check_element(argv[1]) == 0)
                return(EXIT_FAILURE);
        texture = init_list();
        fill_map(argv[1], &texture);
        check_map(&texture);
}
