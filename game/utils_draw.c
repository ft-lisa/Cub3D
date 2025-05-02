/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:22:46 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 11:24:23 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	my_mlx_pixel_put(t_data *texture, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT)
		return ;
	dst = texture->img_ptr + ((y * texture->line_length) + (x
				* (texture->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

void	draw_fov(t_data *game)
{
	float	i;

	game->ddaX = game->dirX;
	game->ddaY = game->dirY;
	i = -30;
	while (i <= 30)
	{
		game->ddaX = game->dirX;
		game->ddaY = game->dirY;
		rotate_vector(game, i);
		line(game, 0);
		i += 0.1;
	}
}
void	line(t_data *texture, int i)
{
	int		length;
	int		px;
	int		py;
	t_ray	ray;

	length = dda(texture, &ray) * CUB_SIZE;
	i = 0;
	while (i <= length)
	{
		px = round(texture->x * CUB_SIZE + texture->ddaX * i);
		py = round(texture->y * CUB_SIZE + texture->ddaY * i);
		my_mlx_pixel_put(texture, px, py, 0xFF0000);
		i++;
	}
}

void	put_square(t_data *texture, int color, float x, float y)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	size = CUB_SIZE - 1;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(texture, x * CUB_SIZE + i, y * CUB_SIZE + j,
				color);
			j++;
		}
		i++;
	}
}

void	rotate_vector(t_data *texture, float angle_degrees)
{
	float	old_x;
	float	old_y;

	old_x = texture->ddaX;
	old_y = texture->ddaY;
	float angle_radians = angle_degrees * PI / 180.0;
		// conversion degrés-> radians
	texture->ddaX = old_x * cos(angle_radians) - old_y * sin(angle_radians);
	texture->ddaY = old_x * sin(angle_radians) + old_y * cos(angle_radians);
}