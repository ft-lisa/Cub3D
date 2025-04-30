#include "../cub3d.h"

/* voir le cas si il y a des espaces derriere est de que il faut prendre e ncompte que toutes les lignes on la meme taille */

void	my_mlx_pixel_put(t_data *texture, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT) // protection
		return ;
	dst = texture->img_ptr + ((y * texture->line_length) + (x
				* (texture->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

void	draw_fov(t_data *game)
{
	float	i;

	game->ddaX = game->dirX;
	game->ddaY = game->dirY;
	i = -30;
	while (i <= 30) // -30 -> +30 degrés (total 60° FOV)
	{
		// Repartir de la direction de base à chaque rayon
		game->ddaX = game->dirX;
		game->ddaY = game->dirY;
		rotate_vector(game, i);
		line(game);
		i += 0.1;
	}
}

void	draw_character(t_data *texture, int center_x, int center_y, int radius,
		int color)
{
	int	x;
	int	y;

	y = -radius + 1;
	while (y <= radius)
	{
		x = -radius + 1;
		while (x <= radius)
		{
			if (x * x + y * y < radius * radius)
				my_mlx_pixel_put(texture, center_x + x, center_y + y, color);
			x++;
		}
		y++;
	}
	draw_fov(texture);
}

void	line(t_data *texture)
{
	int	i;
	int	length;
	int	px;
	int	py;

	length = dda(texture);
	i = 0;
	while (i <= length)
	{
		px = round(texture->x * CUB_SIZE + texture->ddaX * i);
		py = round(texture->y * CUB_SIZE + texture->ddaY * i);
		my_mlx_pixel_put(texture, px, py, 0xFF0000);
		i++;
	}
}

void	put_square(t_data *texture, int color, int size, float x, float y)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			my_mlx_pixel_put(texture, x * CUB_SIZE + i, y * CUB_SIZE + j,
				color);
			j++;
		}
		i++;
	}
}

void	put_background(t_data *texture)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			my_mlx_pixel_put(texture, x, y, 0x808080);
			x++;
		}
		y++;
	}
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
				put_square(texture, 654654, CUB_SIZE -1, j, i);
			else
				put_square(texture, 0, CUB_SIZE -1, j, i);
			j++;
		}
		i++;
	}
	draw_character(texture, texture->x * CUB_SIZE, texture->y * CUB_SIZE, 5,
		16776960);
}

void	init_side(t_ray *ray, t_data *game)
{
	if (game->ddaX < 0)
	{
		ray->stepX = -1;	// dans map_game vers ou on va
		ray->sideDistX = (game->x - ray->x) * ray->deltaDistX;	// combien il manque pour aller de notre float x -> int x
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

void	side_loop(t_ray* ray, t_data* game)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;	// prochaine fois qu'on touche les lignes verticales 
			ray->x = ray->x + ray->stepX;	// avance de un vers ou on va dans map_game
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

double	side_of_wall(t_data *game)
{
	t_ray	ray;

	ray.perpWallDist = 0;
	ray.deltaDistX = fabs(1 / game->ddaX);	// de combien de distance on avance a chaque fois qu'on veut un entier
	ray.deltaDistY = fabs(1 / game->ddaY);
	ray.hit = 0;
	ray.x = (int)game->x;
	ray.y = (int)game->y;
	init_side(&ray, game);
	side_loop(&ray, game);
	if (ray.side == 0 && game->x < ray.x)
		return (EAST);
	else if (ray.side == 0 && game->x > ray.x)
		return (WEST);
	if (game->y < ray.y)
		return (NORTH);
	else
		return (SOUTH);
}

void	draw_vertical_line(t_data *texture, int x, int drawStart, int drawEnd)
{
	int	side;
	int	y;
	int	color;

	side = side_of_wall(texture);
	y = drawStart;
	if (side == NORTH)
		color = 0xff5834;
	else if (side == SOUTH)
		color = 0x34ff39;
	else if (side == WEST)
		color = 0x34a6ff;
	else if (side == EAST)
		color = 0xfc34ff;
	while (y <= drawEnd)
	{
		my_mlx_pixel_put(texture, x, y, color);
		y++;
	}
}

void	draw_wall(t_data *game)
{
	float	x;
	float	perpWallDist;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	float	cameraX;

	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (float)WIDTH - 1;
		game->ddaX = game->dirX + game->planeX * cameraX;
		game->ddaY = game->dirY + game->planeY * cameraX;
		perpWallDist = dda(game);
		lineHeight = (int)(HEIGHT / (perpWallDist * 0.1));
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		draw_vertical_line(game, x, drawStart, drawEnd);
		x += 1;
	}
}

void	rotate_vector(t_data *texture, float angle_degrees)
{
	float	old_x;
	float	old_y;

	old_x = texture->ddaX;
	old_y = texture->ddaY;
	float angle_radians = angle_degrees * PI / 180.0; // conversion degrés -> radians
	texture->ddaX = old_x * cos(angle_radians) - old_y * sin(angle_radians);
	texture->ddaY = old_x * sin(angle_radians) + old_y * cos(angle_radians);
}

void	draw_game(t_data *texture)
{
	mlx_destroy_image(texture->mlx, texture->img);
	texture->img = mlx_new_image(texture->mlx, WIDTH, HEIGHT);
	// put_background(texture);
	put_floor(texture);
	put_ceil(texture);
	draw_wall(texture);
	put_minimap(texture);
	mlx_put_image_to_window(texture->mlx, texture->win, texture->img, 0, 0);
}
