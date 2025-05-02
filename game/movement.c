/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:11:56 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 12:17:14 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_game_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	free_data(t_data *game)
{
	(void)game;
	if (game->map)
		free(game->map);
	if (game->game_map)
		free_game_map(game->game_map);
	if (game->north)
		mlx_destroy_image(game->mlx, game->north);
	if (game->south)
		mlx_destroy_image(game->mlx, game->south);
	if (game->east)
		mlx_destroy_image(game->mlx, game->east);
	if (game->west)
		mlx_destroy_image(game->mlx, game->west);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (1);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307)
		free_data(data);
	if (keycode == 119)
		data->w = 1;
	if (keycode == 115)
		data->s = 1;
	if (keycode == 97)
		data->a = 1;
	if (keycode == 100)
		data->d = 1;
	if (keycode == 65361)
		data->left = 1;
	if (keycode == 65363)
		data->right = 1;
	return (0);
}

// key release
int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->w = 0;
	if (keycode == 115)
		data->s = 0;
	if (keycode == 97)
		data->a = 0;
	if (keycode == 100)
		data->d = 0;
	if (keycode == 65361)
		data->left = 0;
	if (keycode == 65363)
		data->right = 0;
	return (0);
}

int	update(t_data *data)
{
	float	moveSpeed;
	double	oldDirX;
	int		x;
	int		y;

	oldDirX = data->dirX;
	moveSpeed = 0.015;
	if (data->left)
	{
		data->dirX = data->dirX * cos(-moveSpeed) - data->dirY
			* sin(-moveSpeed);
		data->dirY = oldDirX * sin(-moveSpeed) + data->dirY * cos(-moveSpeed);
		data->planeX = -data->dirY * 0.66;
		data->planeY = data->dirX * 0.66;
	}
	if (data->right)
	{
		data->dirX = data->dirX * cos(moveSpeed) - data->dirY * sin(moveSpeed);
		data->dirY = oldDirX * sin(moveSpeed) + data->dirY * cos(moveSpeed);
		data->planeX = -data->dirY * 0.66;
		data->planeY = data->dirX * 0.66;
	}
	if (data->w)
	{
		x = data->x + data->dirX * moveSpeed;
		y = data->y + data->dirY * moveSpeed;
		if (data->game_map[y][x] != '1')
		{
			data->x += data->dirX * moveSpeed;
			data->y += data->dirY * moveSpeed;
		}
	}
	if (data->s)
	{
		x = data->x - data->dirX * moveSpeed;
		y = data->y - data->dirY * moveSpeed;
		if (data->game_map[y][x] != '1')
		{
			data->x -= data->dirX * moveSpeed;
			data->y -= data->dirY * moveSpeed;
		}
	}
	draw_game(data);
	return (0);
}
