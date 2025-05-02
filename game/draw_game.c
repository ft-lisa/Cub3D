/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:05:07 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 11:37:15 by lismarti         ###   ########.fr       */
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

void	draw_vertical_line(t_data *texture, t_ray *ray, int x, int drawStart,
		int drawEnd)
{
	t_tex data;
	data.y = drawStart;
	if (ray->side == 0)
	{
		if (texture->x < ray->x)
		{
			data.tex = texture->west;
			data.texWidth = texture->widthwest;
			data.texHeight = texture->heightwest;
		}
		else
		{
			data.tex = texture->east;
			data.texWidth = texture->widtheast;
			data.texHeight = texture->heighteast;
		}
	}
	else
	{
		if (texture->y < ray->y)
		{
			data.tex = texture->south;
			data.texWidth = texture->widthsouth;
			data.texHeight = texture->heightsouth;
		}
		else
		{
			data.tex = texture->north;
			data.texWidth = texture->widthnorth;
			data.texHeight = texture->heightnorth;
		}
	}
	data.lineHeight = HEIGHT / ray->perpWallDist;
	if (ray->side == 0)
		data.wallX = texture->y + ray->perpWallDist * texture->ddaY;
	else
		data.wallX = texture->x + ray->perpWallDist * texture->ddaX;
	data.wallX -= floor(data.wallX);
	data.texX = (int)(data.wallX * (double)data.texWidth);
	data.step = 1.0 * data.texHeight / (data.lineHeight);
	data.texPos = (drawStart - (-data.lineHeight / 2 + HEIGHT / 2)) * data.step;
	data.info = mlx_get_data_addr(data.tex, &data.bpp, &data.line_length, &data.endian);
	if (!data.info)
	{
		printf("Erreur : donnée de texture non valide !\n");
		free_data(texture);
	}
	while (data.y < drawEnd)
	{
		data.texY = (int)data.texPos;
		if (data.texY >= data.texHeight)
			data.texY = data.texHeight - 1;
		if (data.texY < 0)
			data.texY = 0;
		data.texPos += data.step;
		data.offset = data.texY * data.line_length + data.texX * (data.bpp / 8);
		if (data.texX < 0 || data.texX >= data.texWidth || data.texY < 0 || data.texY >= data.texHeight)
		{
			break ;
		}
		data.color = *(unsigned int *)(data.info + data.offset);
		my_mlx_pixel_put(texture, x, data.y, data.color);
		data.y++;
	}
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
		draw_vertical_line(game, &ray, x, drawStart, drawEnd);
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
