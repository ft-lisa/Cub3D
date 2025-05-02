/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:42:46 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 15:53:52 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	copy_map(int fd, t_data *tex)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			(printf(ERR_CHAR), close(fd), exit(EXIT_FAILURE));
		if (line[0] != '\n')
			break ;
		free(line);
	}
	while (1)
	{
		tex->map = ft_strjoin(tex->map, line);
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (tex->map == NULL)
			(close(fd), exit(EXIT_FAILURE));
	}
	close(fd);
}

void	fill_map(char *file, t_data *tex)
{
	int			fd;
	t_element	element;
	char		*line;
	char		*ori_line;

	element = init_element();
	fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(EXIT_FAILURE);
	while (pass_element(&element) == ERROR)
	{
		line = get_next_line(fd);
		ori_line = line;
		if (*line == 'N' || *line == 'S' || *line == 'W' || *line == 'E')
			texture(line, &element);
		if (*line == 'C' || *line == 'F')
			color(line, &element);
		free(ori_line);
	}
	copy_map(fd, tex);
}

void	swap_n_to_z(char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		line[i] = 0;
}

void	fill_texture_helper(char *line, t_data *texture, int *height,
		int *width)
{
	char	*ori_line;

	ori_line = line;
	if (ft_strlen(line) < 3)
		return ;
	line = line + 3;
	line = pass_space(line);
	swap_n_to_z(line);
	if (ori_line[0] == 'N' && ori_line[1] == 'O' && ori_line[2] == ' ')
	{
		texture->north = mlx_xpm_file_to_image(texture->mlx, line, width,
				height);
		texture->widthnorth = *width;
		texture->heightnorth = *height;
	}
	else if (ori_line[0] == 'S' && ori_line[1] == 'O' && ori_line[2] == ' ')
	{
		texture->south = mlx_xpm_file_to_image(texture->mlx, line, width,
				height);
		texture->widthsouth = *width;
		texture->heightsouth = *height;
	}
}

void	fill_texture_helper2(char *line, t_data *texture, int *height,
		int *width)
{
	char	*ori_line;

	ori_line = line;
	if (ft_strlen(line) < 3)
		return ;
	line = line + 3;
	line = pass_space(line);
	swap_n_to_z(line);
	if (ori_line[0] == 'W' && ori_line[1] == 'E' && ori_line[2] == ' ')
	{
		texture->west = mlx_xpm_file_to_image(texture->mlx, line, width,
				height);
		texture->widthwest = *width;
		texture->heightwest = *height;
	}
	else if (ori_line[0] == 'E' && ori_line[1] == 'A' && ori_line[2] == ' ')
	{
		texture->east = mlx_xpm_file_to_image(texture->mlx, line, width,
				height);
		texture->widtheast = *width;
		texture->heighteast = *height;
	}
}
