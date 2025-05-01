#include "../cub3d.h"

void copy_map(int fd, t_data* tex)
{
        char* line;
        while(1)
        {
                line = get_next_line(fd);
                if (line == NULL)
                        (printf(ERR_CHAR), close(fd), exit(EXIT_FAILURE));
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

void    swap_n_to_z(char *line)
{
        int     i;

        i = 0;
        while (line[i] != '\n' && line[i] != '\0')
                i++;
        if (line[i] == '\n')
                line[i] = 0;
}

void fill_texture(char* line, t_data* texture)
{
        int height = 0;
        int widht = 0;
        char* ori_line;
        (void)texture;

        display_mario_image(texture->mlx, texture->win);
        ori_line = line;
        if (ft_strlen(line) < 3)
                return;
        line = line + 3;
        line = pass_space(line);
        swap_n_to_z(line);
        if (ori_line[0] == 'N' && ori_line[1] == 'O' && ori_line[2] == ' ' )
        {
                texture->north = mlx_xpm_file_to_image(texture->mlx, line, &widht, &height);
                texture->widthnorth = widht;
                texture->heightnorth = height;
        }        
        else if (ori_line[0] == 'S' && ori_line[1] == 'O' && ori_line[2] == ' ' )
        {
                texture->south = mlx_xpm_file_to_image(texture->mlx, line, &widht, &height);
                texture->widthsouth = widht;
                texture->heightsouth = height;
        }
        else if (ori_line[0] == 'W' && ori_line[1] == 'E' && ori_line[2] == ' ' )
        {
                texture->west = mlx_xpm_file_to_image(texture->mlx, line, &widht, &height);
                texture->widthwest = widht;
                texture->heightwest = height;
        }
        if (ori_line[0] == 'E' && ori_line[1] == 'A' && ori_line[2] == ' ' )
        {
                texture->east = mlx_xpm_file_to_image(texture->mlx, line, &widht, &height);
                texture->widtheast = widht;
                texture->heighteast = height;
        }
        
}

void fill_color(char* line, t_data* texture)
{
        int floor;
        int red;
        int blue;
        int green;

        floor = 0;
        if (line[0] == 'F' && line[1] == ' ')
                floor = 1;
        else if (line[0] == 'C' && line[1] == ' ')
                floor = -1;
        if ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ')
        {
                 line++;
                line = pass_space(line);
                red = atoi(line);
                while(*line != ',')
                        line++;
                line++;
                green = atoi(line);
                while(*line != ',')
                        line++;
                line++;
                blue = atoi(line);
        }
        if (floor == 1)
                texture->color_floor = (red << 16) | (green << 8) | blue;
        if (floor == -1)
                texture->color_ceilling = (red << 16) | (green << 8) | blue;   
}

int line_len(char* map, int i)
{
	int j;

	j = 0;
	while(map[i + j] != '\n' && map[i + j] != '\0')
		j++;
	return(j);
}
