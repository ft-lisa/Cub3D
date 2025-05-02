/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:03:35 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 11:04:56 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_ray(t_ray *ray, t_data *game)
{
	if (game->ddaX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (game->x - ray->x) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->x + 1.0 - game->x) * ray->deltaDistX;
	}
	if (game->ddaY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (game->y - ray->y) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->y + 1.0 - game->y) * ray->deltaDistY;
	}
}

void	ray_loop(t_ray *ray, t_data *game)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->x = ray->x + ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->y = ray->y + ray->stepY;
			ray->side = 1;
		}
		if (game->game_map[ray->y][ray->x] == '1')
			ray->hit = 1;
	}
}

double	dda(t_data *game, t_ray *ray)
{
	ray->perpWallDist = 0;
	ray->deltaDistX = fabs(1 / game->ddaX);
	ray->deltaDistY = fabs(1 / game->ddaY);
	ray->hit = 0;
	ray->x = (int)game->x;
	ray->y = (int)game->y;
	init_ray(ray, game);
	ray_loop(ray, game);
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	return (ray->perpWallDist);
}
