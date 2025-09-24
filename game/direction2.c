/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direction2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:50:59 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 16:31:23 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	rotate_left(t_data *data, float move_speed, double old_dir_x)
{
	data->dir_x = data->dir_x * cos(-move_speed) - data->dir_y
		* sin(-move_speed);
	data->dir_y = old_dir_x * sin(-move_speed) + data->dir_y * cos(-move_speed);
	data->plane_x = -data->dir_y * 0.66;
	data->plane_y = data->dir_x * 0.66;
}

void	rotate_right(t_data *data, float move_speed, double old_dir_x)
{
	data->dir_x = data->dir_x * cos(move_speed) - data->dir_y * sin(move_speed);
	data->dir_y = old_dir_x * sin(move_speed) + data->dir_y * cos(move_speed);
	data->plane_x = -data->dir_y * 0.66;
	data->plane_y = data->dir_x * 0.66;
}
