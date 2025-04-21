#ifndef CUB3D_H
# define CUB3D_H

#include "getnextline/get_next_line.h"
#include "checker/err_mess.h"
#include "minilibx-linux/mlx.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

# define ANG_NORTH 90
# define ANG_SOUTH 270
# define ANG_EAST 0
# define ANG_WEST 180

typedef struct s_data
{
	char	*map;
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	void	*mlx;
	void	*win;
	int	color_floor;
	int	color_ceilling;
	float		x;
	float		y;
	int		angle;
}			t_data;

                /* check_map */

int file_browsing(int fd, t_element* map);
int	check_cub(char *str);
int check_element(char* file);
void check_map(t_data* info);

                /* check_color_texture */

void texture(char* line, t_element* map);
int check_num_color(char* line, int comma);
int color(char* line, t_element* map);
void texture(char* line, t_element* map);

                /* init_struct*/

t_element init_element(void);
t_data init_list(void);

                /* fill_struct */

void copy_map(int fd, t_data* tex);               
void fill_map(char* file, t_data* tex);
            
                /* utils */

char* pass_space(char* line);
int pass_element(t_element* map);
char	*ft_strjoin(char const *s1, char const *s2);
int	len_line(char *map, int i);
int	where_in_line(char *map, int i);

#endif