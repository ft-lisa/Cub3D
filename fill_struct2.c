#include "cub3d.h"

// void fill_mlx(t_data* texture)
// {
//         texture->mlx = mlx_init();
// 	if (texture->mlx == NULL)
// 	{
//                 free(texture->map);
//                 exit(EXIT_FAILURE);
//         }
//         texture->win = mlx_new_window(texture->mlx, 1366, 768, "Cub3D");
// }

void	fill_mlx(t_data *texture)
{
	texture->mlx = mlx_init();
	if (texture->mlx == NULL)
	{
		free(texture->map);
		exit(EXIT_FAILURE);
	}
	texture->win = mlx_new_window(texture->mlx, 1366, 768, "Cub3D");
	if (texture->win == NULL)
	{
		free(texture->map);
		mlx_destroy_display(texture->mlx);
		free(texture->mlx);
		exit(EXIT_FAILURE);
	}
	texture->img = mlx_new_image(texture->mlx, 1366, 768);
	if (texture->img == NULL)
	{
		free(texture->map);
		mlx_destroy_window(texture->mlx, texture->win);
		mlx_destroy_display(texture->mlx);
		free(texture->mlx);
		exit(EXIT_FAILURE);
	}
	texture->img_ptr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
}

void	fill_angle(t_data *texture, char lettre)
{
	if (lettre == 'N')
		texture->angle = ANG_NORTH;
	if (lettre == 'S')
		texture->angle = ANG_SOUTH;
	if (lettre == 'W')
		texture->angle = ANG_WEST;
	if (lettre == 'E')
		texture->angle = ANG_EAST;
}

void	fill_pos(t_data *texture)
{
	int	i;
	int	j;

	i = 0;
	while (texture->game_map[i])
	{
		j = 0;
		while (texture->game_map[i][j])
		{
			if (texture->game_map[i][j] == 'N' || texture->game_map[i][j] == 'S'
				|| texture->game_map[i][j] == 'E'
				|| texture->game_map[i][j] == 'W')
			{
				texture->x = j;
				texture->y = i;
				fill_angle(texture, texture->map[i]);
			}
			j++;
		}
		i++;
	}
        texture->size_map = i;
}

int	check_all_fill(t_data *texture)
{
	if (!texture->win || !texture->north || !texture->south || !texture->west
		|| !texture->east)
		return (0);
	return (1);
}

void	fill_struct(t_data *texture, char *file)
{
	char	*line;
	char	*ori_line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		(free(texture->map), exit(EXIT_FAILURE));
	line = get_next_line(fd);
	fill_mlx(texture);
	texture->game_map = ft_split(texture->map, '\n');
	fill_pos(texture);
	while (line != NULL)
	{
		ori_line = line;
		line = pass_space(line);
		fill_color(line, texture);
		fill_texture(line, texture);
		line = get_next_line(fd);
		free(ori_line);
	}
	close(fd);
	// if(check_all_fill(texture) == ERROR)
	// clean_exit(texture);
}
