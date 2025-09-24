/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:24:19 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/06 16:09:28 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_forward(t_data *data, float move_speed)
{
	int	x;
	int	y;

	x = data->x + data->dir_x * move_speed;
	y = data->y + data->dir_y * move_speed;
	if (data->game_map[y][x] != '1' && data->game_map[y][x] != ' '
		&& data->game_map[y][x] != '\0')
	{
		data->x += data->dir_x * move_speed;
		data->y += data->dir_y * move_speed;
	}
}

void	move_backward(t_data *data, float move_speed)
{
	int	x;
	int	y;

	x = data->x - data->dir_x * move_speed;
	y = data->y - data->dir_y * move_speed;
	if (data->game_map[y][x] != '1' && data->game_map[y][x] != ' '
		&& data->game_map[y][x] != '\0')
	{
		data->x -= data->dir_x * move_speed;
		data->y -= data->dir_y * move_speed;
	}
}

void	move_left(t_data *data, float move_speed)
{
	int	x;
	int	y;

	x = data->x - data->plane_x * move_speed;
	y = data->y - data->plane_y * move_speed;
	if (data->game_map[y][x] != '1' && data->game_map[y][x] != ' '
		&& data->game_map[y][x] != '\0')
	{
		data->x -= data->plane_x * move_speed;
		data->y -= data->plane_y * move_speed;
	}
}

void	move_right(t_data *data, float move_speed)
{
	int	x;
	int	y;

	x = data->x + data->plane_x * move_speed;
	y = data->y + data->plane_y * move_speed;
	if (data->game_map[y][x] != '1' && data->game_map[y][x] != ' '
		&& data->game_map[y][x] != '\0')
	{
		data->x += data->plane_x * move_speed;
		data->y += data->plane_y * move_speed;
	}
}
