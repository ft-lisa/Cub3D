#include "cub3d.h"

/* voir le cas si il y a des espaces derriere est de que il faut prendre e ncompte que toutes les lignes on la meme taille */

void	my_mlx_pixel_put(t_data *texture, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > WIDTH || y > HEIGHT) //protection
		return ;
	dst = texture->img_ptr + ((y * texture->line_length)
			+ (x * (texture->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}


void	line(t_data *texture)
{
	int i = 0;
	int length = 50;

	int start_x = texture->x * 32 + 4; 
	int start_y = texture->y * 32  + 4;

	while (i < length)
	{
		int px = start_x + texture->dirX * i;
		int py = start_y + texture->dirY * i;
		my_mlx_pixel_put(texture, px, py, 0xFF0000);
		i++;
	}
}

void put_square(t_data *texture, int color, int size, float x, float y)
{

	int i;
	int j;

	i = 0;
	while(i < size)
	{
		j = 0;
		while(j < size)
		{
			my_mlx_pixel_put(texture, x * CUB_SIZE + i , y * CUB_SIZE + j , color);
			j++;
		}
		i++;
	}
}

void put_background(t_data* texture)
{
	int x;
	int y;

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

void put_minimap(t_data* texture)
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

void draw_game(t_data* texture)
{
	mlx_destroy_image(texture->mlx, texture->img);
	texture->img = mlx_new_image(texture->mlx, WIDTH, HEIGHT);
	put_background(texture);
	put_minimap(texture);
	put_square(texture, 16776960, 8, texture->x, texture->y); // personnage
	line(texture);
	mlx_put_image_to_window(texture->mlx, texture->win, texture->img, 0, 0);
}