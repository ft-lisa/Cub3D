#include "cub3d.h"

void copy_map(int fd, t_data* tex)
{
        char* line;
        while(1)
        {
                line = get_next_line(fd);
                if (line == NULL)
                        (printf(ERR_CHAR), exit(EXIT_FAILURE));
                if (line[0] != '\n')
                        break;
                free(line);
        }
        while(1)
        {
                tex->map = ft_strjoin(tex->map, line);       
                free(line);
                line = get_next_line(fd);
                if (line == NULL)
                        break;
                if (tex->map == NULL) 
                        (close(fd), exit(EXIT_FAILURE));
        }
        close(fd);
}

void fill_map(char* file, t_data* tex)
{
        int fd;
        t_element element;
        char* line;
        char* ori_line;

        element = init_element();
        fd = open(file, O_RDONLY);
        if (fd == -1)
                exit(EXIT_FAILURE);
        while(pass_element(&element) == ERROR)
        {
                line = get_next_line(fd);
                // if (line == NULL)
                //         (printf(ERR_CHAR), exit(EXIT_FAILURE));
                ori_line = line;
                if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
                        texture(line, &element);
                if (*line == 'C' || *line == 'F')
                        color(line, &element);
                free(ori_line);
        }
        copy_map(fd, tex);
}
