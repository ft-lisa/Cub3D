#include "cub3d.h"

#include <stdio.h>

void	print_data(t_data *data)
{
	printf("Map: %s\n", data->map);
	printf("North: %p\n", data->north);
	printf("South: %p\n", data->south);
	printf("East: %p\n", data->east);
	printf("West: %p\n", data->west);
	printf("MLX: %p\n", data->mlx);
	printf("Win: %p\n", data->win);
	printf("Color Floor: %d\n", data->color_floor);
	printf("Color Ceiling: %d\n", data->color_ceilling);
	printf("Position X: %.2f\n", data->x);
	printf("Position Y: %.2f\n", data->y);
}


void fill_texture(char* line, t_data* texture)
{
        int height;

        height = 0;
        if (ft_strlen(line) < 3)
                return;
        if (line[0] == 'N' && line[1] == 'O' && line[2] == ' ' )
                texture->north = mlx_xpm_file_to_image(texture->mlx, line, &height, &height);
        else if (line[0] == 'S' && line[1] == 'O' && line[2] == ' ' )
                texture->south = mlx_xpm_file_to_image(texture->mlx, line, &height, &height);
        else if (line[0] == 'W' && line[1] == 'E' && line[2] == ' ' )
                texture->west = mlx_xpm_file_to_image(texture->mlx, line, &height, &height);
        else if (line[0] == 'E' && line[1] == 'A' && line[2] == ' ' )
                texture->east = mlx_xpm_file_to_image(texture->mlx, line, &height, &height);
}

void fill_color(char* line, t_data* texture)
{
        int floor;
        int red;
        int blue;
        int green;

        floor = 0;
        if (line[0] == 'C')
                floor = 1;
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
                printf("r: %d, g: %d, b: %d\n", red, green, blue);
        }
        if (floor)
                texture->color_floor = (red << 16) | (green << 8) | blue;
        else
                texture->color_ceilling = (red << 16) | (green << 8) | blue;   
}

void fill_mlx(t_data* texture)
{
        texture->mlx = mlx_init();
	if (texture->mlx == NULL)
	{
                free(texture->map);
                exit(EXIT_FAILURE);
        }
        texture->win = mlx_new_window(texture->mlx, 1366, 768, "Cub3D");
        // mettre la position du joueur
}

int check_all_fill(t_data* texture)
{
        if (!texture->win || !texture->north || !texture->south || !texture->west || !texture->east)
                return(0);
        return(1);
}

void fill_struct(t_data *texture, char* file)
{
        char* line;
        char* ori_line;
        int fd;

        fd = open(file, O_RDONLY);
        if (fd == -1)
                (free(texture->map), exit(EXIT_FAILURE));
        line = get_next_line(fd);
        fill_mlx(texture);
        while(line != NULL)
        {
                ori_line = line;
                line = pass_space(line);
                fill_color(line, texture);
                fill_texture(line, texture);
                line = get_next_line(fd);
                free(ori_line);
        }
        close(fd);
        //if(check_all_fill(texture) == ERROR)
                //clean_exit(texture);
}

int     main(int argc, char** argv)
{        
        t_data texture;

        if (argc != 2)
                return(printf(ERR_ARG), EXIT_FAILURE);
        if (check_element(argv[1]) == 0)
                return(EXIT_FAILURE);
        texture = init_list();
        fill_map(argv[1], &texture);
        check_map(&texture);
        fill_struct(&texture, argv[1]);
        print_data(&texture);
        return(0);
}