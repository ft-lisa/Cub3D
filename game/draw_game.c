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
}

void	line(t_data *texture)
{
	int i;
	int	length;
	int		px;
	int		py;

	length = dda(texture);
	i = 0;
	while (i <= length)
	{
		px = round(texture->x * CUB_SIZE + texture->ddaX * i);
		py = round(texture->y * CUB_SIZE+ texture->ddaY * i);
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
				put_square(texture, 654654, 31, j, i);
			else
				put_square(texture, 0, 31, j, i);
			j++;
		}
		i++;
	}
}

#include <math.h>

void rotate_vector(t_data *texture, float angle_degrees)
{
	float old_x = texture->ddaX;
	float old_y = texture->ddaY;
    float angle_radians = angle_degrees * PI / 180.0; // conversion degrés -> radians

    texture->ddaX = old_x * cos(angle_radians) - old_y * sin(angle_radians);
    texture-> ddaY = old_x * sin(angle_radians) + old_y * cos(angle_radians);
}


void	draw_game(t_data *texture)
{
	texture->ddaX = texture->dirX;
	texture->ddaY = texture->dirY;
	float i = -30;
	mlx_destroy_image(texture->mlx, texture->img);
	texture->img = mlx_new_image(texture->mlx, WIDTH, HEIGHT);
	put_background(texture);
	put_minimap(texture);
	// put_square(texture, 16776960, 8, texture->x, texture->y); // personnage
	draw_character(texture, texture->x * 32, texture->y * 32, 5, 16776960);
	while (i <= 30) // -30 -> +30 degrés (total 60° FOV)
	{
		// Repartir de la direction de base à chaque rayon
		texture->ddaX = texture->dirX;
		texture->ddaY = texture->dirY;
		rotate_vector(texture, i);
		line(texture);
		i += 0.1;
	}	
	mlx_put_image_to_window(texture->mlx, texture->win, texture->img, 0, 0);
}
