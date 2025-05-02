/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:07 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 12:11:20 by lismarti         ###   ########.fr       */
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

void	put_background(t_data *texture)
{
	int	x;
	int	y;

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
	int		line_height;
	float	camera_x;
	t_ray	ray;

	x = 0;
	while (x < WIDTH)
	{
		camera_x = 2 * x / (float)WIDTH - 1;
		game->ddaX = game->dirX + game->planeX * camera_x;
		game->ddaY = game->dirY + game->planeY * camera_x;
		dda(game, &ray);
		line_height = (int)(HEIGHT / (ray.perpWallDist));
		ray.draw_start = -line_height / 2 + HEIGHT / 2;
		if (ray.draw_start < 0)
			ray.draw_start = 0;
		ray.draw_end = line_height / 2 + HEIGHT / 2;
		if (ray.draw_end >= HEIGHT)
			ray.draw_end = HEIGHT - 1;
		draw_texture_line(game, &ray, x);
		x += 1;
	}
}

void	draw_game(t_data *texture)
{
	mlx_destroy_image(texture->mlx, texture->img);
	texture->img = mlx_new_image(texture->mlx, WIDTH, HEIGHT);
	put_background(texture);
	draw_wall(texture);
	put_minimap(texture);
	mlx_put_image_to_window(texture->mlx, texture->win, texture->img, 0, 0);
}
