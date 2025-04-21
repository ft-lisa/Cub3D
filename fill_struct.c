#include "cub3d.h"

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
        // int floor;
        // int red;
        // int blue;
        // int green;
		(void)texture;

        // floor = 0;
        // if (line[0] == 'C')
        //         floor = 1;
        // if ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ')
        // {
                 line++;
        //         line = pass_space(line);
        //         red = atoi(line);
        //         while(*line != ',')
        //                 line++;
        //         line++;
        //         green = atoi(line);
        //         while(*line != ',')
        //                 line++;
        //         line++;
        //         blue = atoi(line);
        //         // printf("r: %d, g: %d, b: %d\n", red, green, blue);
        // }
//         if (floor)
//                 texture->color_floor = (red << 16) | (green << 8) | blue;
//         else
//                 texture->color_ceilling = (red << 16) | (green << 8) | blue;   
}

int line_len(char* map, int i)
{
	int j;

	j = 0;
	while(map[i + j] != '\n' && map[i + j] != '\0')
		j++;
	return(j);
}

void map_to_game_map(t_data* texture)
{
	int	i;
	int num_bn;
	int	j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	num_bn = 0;
	while (texture->map[i])
	{
		if (texture->map[i] == '\n')
			num_bn++;
		i++;
	}
	printf("num_nb : %d\n", num_bn);
	texture->game_map = malloc(sizeof(char*) * num_bn + 1);
	if (!texture->game_map)
		exit(1); // map malloc peut etre mlx
	i = 0;
	while (texture->map[i])
	{
		if(texture->map[i] == '\n' || i == 0)
		{
			texture->game_map[j] = malloc(sizeof(char) * line_len(texture->map, i + 1) + 1);
			printf("len_line : %d\n", line_len(texture->map, i + 1));
			if (!texture->game_map[j])
				exit(1); //FREE !!
			j++;
		}	
		i++;
	}
	i = 0;
	j = 0;
	while(texture->map[k])
	{
		if (texture->map[k] == '\n')
		{
			texture->game_map[i][j] = '\0';
			i++;
			j = 0;
			k++;
		}
		texture->game_map[i][j] = texture->map[k];
		j++;
		k++;
	}
}


// FT_TROPNULL
// void map_to_game_map(t_data* texture)
// {
// 	int	i;
// 	int num_bn;
// 	int	j;
// 	int k;

// 	i = 0;
// 	j = 0;
// 	k = 0;
// 	num_bn = 0;
// 	while (texture->map[i])
// 	{
// 		if (texture->map[i] == '\n')
// 			num_bn++;
// 		i++;
// 	}
// 	printf("num_nb : %d\n", num_bn);
// 	texture->game_map = malloc(sizeof(char*) * num_bn + 1);
// 	if (!texture->game_map)
// 		exit(1); // map malloc peut etre mlx
// 	i = 0;
// 	while (texture->map[i])
// 	{
// 		if(texture->map[i] == '\n' || i == 0)
// 		{
// 			texture->game_map[j] = malloc(sizeof(char) * line_len(texture->map, i + 1) + 1);
// 			printf("len_line : %d\n", line_len(texture->map, i + 1));
// 			if (!texture->game_map[j])
// 				exit(1); //FREE !!
// 			j++;
// 		}	
// 		i++;
// 	}
// 	i = 0;
// 	j = 0;
// 	while(texture->map[k])
// 	{
// 		if (texture->map[k] == '\n')
// 		{
// 			texture->game_map[i][j] = '\0';
// 			i++;
// 			j = 0;
// 			k++;
// 		}
// 		texture->game_map[i][j] = texture->map[k];
// 		j++;
// 		k++;
// 	}
// }
