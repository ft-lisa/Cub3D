#include "../cub3d.h"

void init_ray(t_ray *ray, t_data *game)
{
	if (game->ddaX < 0)
	{
		ray->stepX = -1;						// dans map_game vers ou on va
		ray->sideDistX = (game->x - ray->x) * ray->deltaDistX;		// combien il manque pour aller de notre float x -> int x
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

void ray_loop(t_ray* ray, t_data* game)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;			// prochaine fois qu'on touche les lignes verticales 
			ray->x = ray->x + ray->stepX;				// avance de un vers ou on va dans map_game
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->y = ray->y + ray->stepY;
			ray->side = 1;
		}
		if (game->game_map[ray->y][ray->x] == '1') // mur ?
			ray->hit = 1;
	}
}

double	dda(t_data *game, t_ray* ray)
{

	ray->perpWallDist = 0;
	ray->deltaDistX = fabs(1 / game->ddaX);					// de combien de distance on avance a chaque fois qu'on veut un entier
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
	return(ray->perpWallDist * CUB_SIZE);
}