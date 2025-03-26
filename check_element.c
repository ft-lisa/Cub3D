#include "err_mess.h"
#include "cub3d.h"

void texture(char* line, t_element* map)
{
        if (ft_strlen(line) < 3)
                return;
        if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ' )
                map->no++;
        else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ' )
                map->so++;
        else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ' )
                map->we++;
        else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ' )
                map->ea++;      
}

/* 
F 220,100,0
F 220,100,0,
F 220,10a0,0
F 2200,100,0
F     220,100,0
F 220,100
F 220,100,
F 220,110,0a
F 220,100,0
F     220,100,0
F 220,100,51,54,
*/

int check_num_color(char* line)
{
        int num;
        int comma;
        int cont;

        comma = 0;
        while(*line != '\0')
        {
                num = 0;
                cont = 0;
                while(*line >= '0' && *line <= '9')
                {
                        cont = 1;
                        num = num * 10 + *line - 48;
                        line++;
                }
                printf("%d, %d\n", num, cont);
                if (num > 255 || cont == 0)
                        return(printf(ERR_COLOR), ERROR);
                if (*line != ',' && *line != '\n')
                        return(printf(ERR_COLOR), ERROR);
                comma++;
                line++;
        }
        printf("%d\n", comma);
        if (comma == 2)
                return(GOOD);
        return(printf(ERR_COLOR), ERROR);
}

int color(char* line, t_element* map)
{
        if (line[0] == 'C' && line[1] == ' ')
                map->c++;
        else if (line[0] == 'F' && line[1] == ' ')
                map->f++;
        else
                return(GOOD);
        line++;
        line = pass_space(line);
        return(check_num_color(line));
        
}

int file_browsing(int fd, t_element* map)
{
        char* line;
        char* ori_line;
        
        line = get_next_line(fd);
        ori_line = line;
        while (line != NULL)
        {
                
                line = pass_space(line);
                if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
                        texture(line, map);
                if (*line == 'C' || *line == 'F')
                        if (color(line, map) == ERROR)
                                return(ERROR);
                free(ori_line);
                line = get_next_line(fd);
                ori_line = line;
        }
        return(GOOD);
}

int	check_cub(char *str)
{
	int	i;

	i = ft_strlen(str);
        if (i < 4)
                return(printf(ERR_CUB), ERROR);
	if (str[i - 1] != 'b' || str[i - 2] != 'u' || str[i - 3] != 'c' || str[i
			- 4] != '.')
		return (printf(ERR_CUB), ERROR);
	return (GOOD);
}

int check_map(char* file)
{
        int fd;
        t_element element;

        if (check_cub(file) == ERROR)
                return(ERROR);
        fd = open(file, O_RDONLY);
        if (fd == -1)
                return(printf(ERR_FILE), ERROR);
        element = init_element();
        if (file_browsing(fd, &element) == ERROR)
                return(close (fd), ERROR);
        return(GOOD);
}
