#include "err_mess.h"
#include "cub3d.h"

int     main(int argc, char** argv)
{
        if (argc != 2)
                return(printf(ERR_ARG), EXIT_FAILURE);
        if (check_map(argv[1]) == 0)
                return(EXIT_FAILURE);
}