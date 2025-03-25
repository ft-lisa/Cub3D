#ifndef ERR_MESS_H
# define ERR_MESS_H

# define GOOD_EXIT 0
# define EXIT_FAILURE 1
# define GOOD 1
# define ERROR 0

# define ERR_ARG "./cub3d [file]\n"
# define ERR_CUB "The file is not a .cub\n"
# define ERR_FILE "This is not a file\n"

typedef struct s_element
{
    int no;
    int so;
    int we;
    int ea;
    int f;
    int c;
}	                    t_element;

#endif