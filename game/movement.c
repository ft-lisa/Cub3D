/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:11:56 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/06 16:09:31 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	float	move_speed;
	double	old_dir_x;

	move_speed = 0.015;
	old_dir_x = data->dir_x;
	if (data->left)
		rotate_left(data, move_speed, old_dir_x);
	if (data->right)
		rotate_right(data, move_speed, old_dir_x);
	if (data->w)
		move_forward(data, move_speed);
	if (data->s)
		move_backward(data, move_speed);
	if (data->a)
		move_left(data, move_speed);
	if (data->d)
		move_right(data, move_speed);
	draw_game(data);
	return (0);
}
