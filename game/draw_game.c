/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:07 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 11:53:22 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_character(t_data *texture, int radius)
{
	int	x;
	int	y;
	int	center_x;
	int	center_y;

	center_x = texture->x * CUB_SIZE;
	center_y = texture->y * CUB_SIZE;
	y = -radius + 1;
	while (y <= radius)
	{
		x = -radius + 1;
		while (x <= radius)
		{
			if (x * x + y * y < radius * radius)
				my_mlx_pixel_put(texture, center_x + x, center_y + y, 16776960);
			x++;
		}
		y++;
	}
	draw_fov(texture);
}

void	put_floor(t_data *texture)
{
	int	x;
	int	y;

	x = 0;
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(texture, x, y, texture->color_floor);
			x++;
		}
		y++;
	}
}

void	put_ceil(t_data *texture)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT / 2)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(texture, x, y, texture->color_ceilling);
			x++;
		}
		y++;
	}
}

void	put_minimap(t_data *texture)
{
	int	i;
	int	j;

	i = 0;
	while (texture->game_map[i])
	{
		j = 0;
		while (texture->game_map[i][j])
		{
			if (texture->game_map[i][j] == '1')
				put_square(texture, 654654, j, i);
			else
				put_square(texture, 0, j, i);
			j++;
		}
		i++;
	}
	draw_character(texture, 5);
}

void	draw_wall(t_data *game)
{
	float	x;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	float	cameraX;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (float)WIDTH - 1;
		game->ddaX = game->dirX + game->planeX * cameraX;
		game->ddaY = game->dirY + game->planeY * cameraX;
		dda(game, &ray);
		lineHeight = (int)(HEIGHT / (ray.perpWallDist)); // avoid division by 0
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		draw_texture_line(game, &ray, x, drawStart, drawEnd);
		x += 1;
	}
}



void	draw_game(t_data *texture)
{
	mlx_destroy_image(texture->mlx, texture->img);
	texture->img = mlx_new_image(texture->mlx, WIDTH, HEIGHT);
	// put_background(texture);
	put_ceil(texture);
	put_floor(texture);
	draw_wall(texture);
	put_minimap(texture);
	mlx_put_image_to_window(texture->mlx, texture->win, texture->img, 0, 0);
}
