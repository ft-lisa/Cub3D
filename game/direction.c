/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:24:19 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 12:25:08 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_data *data, float move_speed, double old_dir_x)
{
	data->dirX = data->dirX * cos(-move_speed) - data->dirY * sin(-move_speed);
	data->dirY = old_dir_x * sin(-move_speed) + data->dirY * cos(-move_speed);
	data->planeX = -data->dirY * 0.66;
	data->planeY = data->dirX * 0.66;
}

void	rotate_right(t_data *data, float move_speed, double old_dir_x)
{
	data->dirX = data->dirX * cos(move_speed) - data->dirY * sin(move_speed);
	data->dirY = old_dir_x * sin(move_speed) + data->dirY * cos(move_speed);
	data->planeX = -data->dirY * 0.66;
	data->planeY = data->dirX * 0.66;
}

void	move_forward(t_data *data, float move_speed)
{
	int	x;
	int	y;

	x = data->x + data->dirX * move_speed;
	y = data->y + data->dirY * move_speed;
	if (data->game_map[y][x] != '1')
	{
		data->x += data->dirX * move_speed;
		data->y += data->dirY * move_speed;
	}
}

void	move_backward(t_data *data, float move_speed)
{
	int	x;
	int	y;

	x = data->x - data->dirX * move_speed;
	y = data->y - data->dirY * move_speed;
	if (data->game_map[y][x] != '1')
	{
		data->x -= data->dirX * move_speed;
		data->y -= data->dirY * move_speed;
	}
}
