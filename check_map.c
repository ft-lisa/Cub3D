#include "err_mess.h"
#include "cub3d.h"
char* pass_space(char* line)
{
        while(*line != '\0' && *line == ' ')
                line++;
        return(line);
}

int file_browsing(int fd)
{
        char* line;

        line = get_next_line(fd);
        while (line != NULL)
        {
                line = get_next_line(fd);
                line = pass_space(line);
                if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
                        texture(line);
                if (*line == 'C' || *line == 'F')
                        color(line);
        }
        return(0);
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

        if (check_cub(file) == ERROR)
                return(ERROR);
        fd = open(file, O_RDONLY);
        if (fd == -1)
                return(printf(ERR_FILE), ERROR);
        if (file_browsing(fd) == ERROR)
                return(ERROR);
        return(GOOD);
}
