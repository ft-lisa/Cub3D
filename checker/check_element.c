#include "../cub3d.h"

int check_the_number(t_element* map)
{
        if (map->ea < 1 || map->no < 1 || map->so < 1 || map->we < 1)
                return(printf(ERR_MISS_TEX), ERROR);
        if (map->ea > 1 || map->no > 1 || map->so > 1 || map->we > 1)
                return(printf(ERR_MUCH_TEX), ERROR);
        if (map->f < 1 || map->c < 1)
                return(printf(ERR_MISS_COL), ERROR);
        if (map->f > 1 || map->c > 1)
                return(printf(ERR_MUCH_COL), ERROR);
        return(GOOD);
}

int file_browsing(int fd, t_element* map)
{
        char* line;
        char* ori_line;
        
        line = get_next_line(fd);
        while (line != NULL)
        {
                // printf("line: %s", line);
                ori_line = line;
                line = pass_space(line);
                if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
                        texture(line, map);
                if (*line == 'C' || *line == 'F')
                        if (color(line, map) == ERROR)
                                return(free(ori_line), get_next_line(-1), ERROR);
                free(ori_line);
                line = get_next_line(fd);
        }
        return(check_the_number(map));
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

int check_element(char* file)
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
        close(fd);
        return(GOOD);
}
