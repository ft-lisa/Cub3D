#ifndef CUB3D_H
# define CUB3D_H

#include "getnextline/get_next_line.h"
#include "checker/err_mess.h"

#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

                /* check_map */

int file_browsing(int fd, t_element* map);
int	check_cub(char *str);
int check_map(char* file);

                /* check_color_texture */

void texture(char* line, t_element* map);
int check_num_color(char* line, int comma);
int color(char* line, t_element* map);

                /* init_struct*/

t_element init_element(void);

                /* utils */

char* pass_space(char* line);

#endif