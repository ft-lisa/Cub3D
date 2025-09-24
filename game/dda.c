/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:03:35 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 16:09:21 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_ray *ray, t_data *game)
{
	if (game->dda_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (game->x - ray->x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->x + 1.0 - game->x) * ray->deltadist_x;
	}
	if (game->dda_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (game->y - ray->y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->y + 1.0 - game->y) * ray->deltadist_y;
	}
}

void	ray_loop(t_ray *ray, t_data *game)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->x = ray->x + ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->y = ray->y + ray->step_y;
			ray->side = 1;
		}
		if (game->game_map[ray->y][ray->x] == '1')
			ray->hit = 1;
	}
}

double	dda(t_data *game, t_ray *ray)
{
	ray->perpwalldist = 0;
	ray->deltadist_x = fabs(1 / game->dda_x);
	ray->deltadist_y = fabs(1 / game->dda_y);
	ray->hit = 0;
	ray->x = (int)game->x;
	ray->y = (int)game->y;
	init_ray(ray, game);
	ray_loop(ray, game);
	if (ray->side == 0)
		ray->perpwalldist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->perpwalldist = (ray->sidedist_y - ray->deltadist_y);
	return (ray->perpwalldist);
}
