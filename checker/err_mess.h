#ifndef ERR_MESS_H
# define ERR_MESS_H

# define GOOD_EXIT 0
# define EXIT_FAILURE 1
# define GOOD 1
# define ERROR 0

# define ERR_ARG "./cub3d [file]\n"
# define ERR_CUB "The file is not a .cub\n"
# define ERR_FILE "This is not a file\n"
# define ERR_COLOR "colors R,G,B range [0,255]\n"
# define ERR_MISS_TEX "It's necessary a texture for NO, SO, EA and WE\n"
# define ERR_MUCH_TEX "It's necessary ONE texture for NO, SO, EA and WE\n"
# define ERR_MISS_COL "It's necessary a color for F and C\n"
# define ERR_MUCH_COL "It's necessary ONE color for F and C\n"
# define ERR_CHAR "Map must contain only: 0, 1, N, S, W, E\n"
# define ERR_SPAWN "The map must contain a N, S, W or E\n"
# define ERR_MULT_SPAWN "The map must contain one N, S, W or E\n"
# define ERR_EMPTY "There is in the map an empty line\n"
# define ERR_WALL "The wall is not complete\n"

typedef struct s_element
{
	int	no;
	int	so;
	int	we;
	int	ea;
	int	f;
	int	c;
}		t_element;

#endif