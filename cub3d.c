#include "cub3d.h"
#include <stdio.h>

void	print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("Map: %s\n", data->map ? data->map : "null");
	printf("North: %s\n", data->north ? "loaded" : "null");
	printf("South: %s\n", data->south ? "loaded" : "null");
	printf("East: %s\n", data->east ? "loaded" : "null");
	printf("West: %s\n", data->west ? "loaded" : "null");
	printf("MLX: %s\n", data->mlx ? "init" : "null");
	printf("Win: %s\n", data->win ? "open" : "null");
	printf("Color Floor: %d\n", data->color_floor);
	printf("Color Ceiling: %d\n", data->color_ceilling);
	printf("Position X: %.2f\n", data->x);
	printf("Position Y: %.2f\n", data->y);
	if (data->game_map)
	{
		while (data->game_map[i])
		{
			printf("%s\n", data->game_map[i]);
			i++;
		}
	}
	else
		printf("Game Map: null\n");
}

float	dda(t_data *game)
{
	int		hit;
	int		stepX;
	int		stepY;
	int x;
	int y;
	float	nextX;
	float	nextY;
	float	deltaDistX;
	float	deltaDistY;
	float	sideDistX;
	float	sideDistY;
	int side;
	deltaDistX = fabs(1 / game->dirX);
	deltaDistY = fabs(1 / game->dirY);
	
	nextX = game->x;
	nextY = game->y;
	hit = 0;
	x = game->x;
	y = game->y;
	if (game->dirX < 0)
	{
		stepX = -1;
		sideDistX = (game->x - x) * deltaDistX;
	}
	else
	{
		stepX = 1;
		sideDistX = (x + 1.0 - game->x) * deltaDistX;
	}
	if (game->dirY < 0)
	{
		stepY = -1;
		sideDistY = (game->y - y) * deltaDistY;
	}
	else
	{
		stepY = 1;
		sideDistY = (y + 1.0 - game->y) * deltaDistY;
	}
	while (hit == 0)
	{
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			x = x + stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			y = y + stepY;
			side = 1;
		}
		if (game->game_map[y][x] == '1') // mur ?
			hit = 1;
	}
	if (side == 0)
		return (sideDistX - deltaDistX);
	else
		return (sideDistY - deltaDistY);
}

// float	dda(t_data *game, float rayDirX, float rayDirY)
// {
// 	int		mapX;
// 	int		mapY;
// 	float	deltaDistX;
// 	float	deltaDistY;
// 	int		stepX;
// 	int		stepY;
// 	float	sideDistX;
// 	float	sideDistY;
// 	int		hit;

// 	mapX = (int)game->x;
// 	mapY = (int)game->y;
// 	deltaDistX = fabs(1 / rayDirX);
// 	deltaDistY = fabs(1 / rayDirY);
// 	if (rayDirX < 0)
// 	{
// 		stepX = -1;
// 		sideDistX = (game->x - mapX) * deltaDistX;
// 	}
// 	else
// 	{
// 		stepX = 1;
// 		sideDistX = (mapX + 1.0 - game->x) * deltaDistX;
// 	}
// 	if (rayDirY < 0)
// 	{
// 		stepY = -1;
// 		sideDistY = (game->y - mapY) * deltaDistY;
// 	}
// 	else
// 	{
// 		stepY = 1;
// 		sideDistY = (mapY + 1.0 - game->y) * deltaDistY;
// 	}
// 	hit = 0;
// 	int side; // 0 si vertical, 1 si horizontal
// 	while (hit == 0)
// 	{
// 		if (sideDistX < sideDistY)
// 		{
// 			sideDistX += deltaDistX;
// 			mapX += stepX;
// 			side = 0;
// 		}
// 		else
// 		{
// 			sideDistY += deltaDistY;
// 			mapY += stepY;
// 			side = 1;
// 		}
// 		if (game->map[mapY][mapX] == '1') // mur ?
// 			hit = 1;
// 	}
// 	if (side == 0)
// 		return (sideDistX - deltaDistX);
// 	else
// 		return (sideDistY - deltaDistY);
// }

int	main(int argc, char **argv)
{
	t_data	texture;

	if (argc != 2)
		return (printf(ERR_ARG), EXIT_FAILURE);
	if (check_element(argv[1]) == 0)
		return (EXIT_FAILURE);
	texture = init_list();
	fill_map(argv[1], &texture);
	check_map(&texture);
	fill_struct(&texture, argv[1]);
	// print_data(&texture);
	draw_game(&texture);
	mlx_hook(texture.win, 2, 1L << 0, key_press, &texture);   // Key down
	mlx_hook(texture.win, 3, 1L << 1, key_release, &texture); // Key up
	mlx_loop_hook(texture.mlx, update, &texture);             // Loop update
	mlx_loop(texture.mlx);
	return (0);
}
