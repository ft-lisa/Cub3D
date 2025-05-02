/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:47:30 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 15:50:18 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	fill_texture(char *line, t_data *texture)
{
	int	height;
	int	width;

	(void)texture;
	height = 0;
	width = 0;
	display_mario_image(texture->mlx, texture->win);
	fill_texture_helper(line, texture, &height, &width);
	fill_texture_helper2(line, texture, &height, &width);
}

void	fill_color(char *line, t_data *texture, int floor, int red)
{
	int	blue;
	int	green;

	if (line[0] == 'F' && line[1] == ' ')
		floor = 1;
	else if (line[0] == 'C' && line[1] == ' ')
		floor = -1;
	if ((line[0] == 'C' || line[0] == 'F') && line[1] == ' ')
	{
		line++;
		line = pass_space(line);
		red = atoi(line);
		while (*line != ',')
			line++;
		line++;
		green = atoi(line);
		while (*line != ',')
			line++;
		line++;
		blue = atoi(line);
	}
	if (floor == 1)
		texture->color_floor = (red << 16) | (green << 8) | blue;
	if (floor == -1)
		texture->color_ceilling = (red << 16) | (green << 8) | blue;
}
