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
	//draw_fov(texture);
}

void	line(t_data *texture)
{
	int	i;
	int	length;
	int	px;
	int	py;
	t_ray ray;

	length = dda(texture, &ray);
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
				put_square(texture, 654654, CUB_SIZE - 1, j, i);
			else
				put_square(texture, 0, CUB_SIZE - 1, j, i);
			j++;
		}
		i++;
	}
	draw_character(texture, texture->x * CUB_SIZE, texture->y * CUB_SIZE, 5,
		16776960);
}

void	draw_vertical_line(t_data *texture, t_ray* ray, int x, int drawStart, int drawEnd)
{
	int		y;
	int		texX, texY;
	int		color;
	double	step;
	double	texPos;
	void	*tex;
	int		texWidth;
	int		texHeight;
	int bpp, line_length, endian;
	
	y = drawStart;
	if (ray->side == 0)
	{
		if (texture->x < ray->x)
		{
			tex = texture->east;
			texWidth = texture->widtheast;
			texHeight = texture->heighteast;
		}
		else
		{
			tex = texture->east;
			texWidth = texture->widtheast;
			texHeight = texture->heighteast;	
		}
	}
	else
	{
		if (texture->y < ray->y)
		{
			tex = texture->east;
			texWidth = texture->widtheast;
			texHeight = texture->heighteast;	
		}
		else
		{
			tex = texture->east;
			texWidth = texture->widtheast;
			texHeight = texture->heighteast;
		}
	}
// 	    printf("=== Debug Raycasting ===\n");
// printf("ray->side       = %d\n", ray->side);
// printf("ray->x          = %d\n", ray->x);
// printf("ray->y          = %d\n", ray->y);
// printf("ray->perpWallDist = %f\n", ray->perpWallDist);
// printf("texture->x      = %f\n", texture->x);
// printf("texture->y      = %f\n", texture->y);
// printf("texture->ddaX   = %f\n", texture->ddaX);
// printf("texture->ddaY   = %f\n", texture->ddaY);
// printf("texWidth        = %d\n", texWidth);
// printf("texHeight       = %d\n", texHeight);
// printf("drawStart       = %d\n", drawStart);
// printf("drawEnd         = %d\n", drawEnd);
// printf("HEIGHT          = %d\n", HEIGHT);
// printf("wallX (fract)   = %f\n", wallX);
// printf("texX            = %d\n", texX);
// printf("step            = %f\n", step);
// printf("texPos          = %f\n", texPos);
// printf("bpp             = %d\n", bpp);
// printf("line_length     = %d\n", line_length);
// printf("endian          = %d\n", endian);
    double wallX;
	if (ray->side == 0)
		wallX = texture->y + ray->perpWallDist * texture->ddaY;
	else
		wallX = texture->x + ray->perpWallDist * texture->ddaX;

    wallX -= floor(wallX);
    texX = (int)(wallX * (double)texWidth);
    if ((ray->side == 0 && ray->x > texture->x) || (ray->side == 1 && ray->y < texture->y))
        texX = texWidth - texX - 1;
    if (texX < 0) texX = 0;
    if (texX >= texWidth) texX = texWidth - 1;
    step = 1.0 * texHeight / (drawEnd - drawStart);
    texPos = (drawStart - HEIGHT / 2 + (drawEnd - drawStart) / 2) * step;
    char *data = mlx_get_data_addr(tex, &bpp, &line_length, &endian);
    if (!data)
    {
        printf("Erreur : donnée de texture non valide !\n");
        exit(1);
    }
    while (y < drawEnd)
    {
        texY = (int)texPos;
        if (texY >= texHeight) texY = texHeight - 1;
        if (texY < 0) texY = 0;
        
        texPos += step;
        int offset = texY * line_length + texX * (bpp / 8);
        if (texX < 0 || texX >= texWidth || texY < 0 || texY >= texHeight)
        {
            break;
        }
        color = *(unsigned int *)(data + offset);
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
	t_ray ray;

	x = 0;
	while (x < WIDTH)
	{
		cameraX = 2 * x / (float)WIDTH - 1;
		game->ddaX = game->dirX + game->planeX * cameraX;
		game->ddaY = game->dirY + game->planeY * cameraX;
		// cameraX = 2 * x / (float)WIDTH - 1;
		// game->ddaX = game->dirX + game->planeX * cameraX;
		// game->ddaY = game->dirY + game->planeY * cameraX;

		// float ray_length = dda(game, &ray);
		// perpWallDist = ray_length * (game->dirX * game->ddaX + game->dirY * game->ddaY)
        //                          / (sqrt(game->ddaX * game->ddaX + game->ddaY * game->ddaY));

		perpWallDist = dda(game, &ray);
		lineHeight = (int)(HEIGHT / (ray.perpWallDist + 0.0001)); // avoid division by 0
		drawStart = -lineHeight / 2 + HEIGHT / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + HEIGHT / 2;
		if (drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;
		draw_vertical_line(game, &ray, x, drawStart, drawEnd);
		x += 1;
	}
}

void	rotate_vector(t_data *texture, float angle_degrees)
{
	float	old_x;
	float	old_y;

	old_x = texture->ddaX;
	old_y = texture->ddaY;
	float angle_radians = angle_degrees * PI / 180.0; // conversion degrés-> radians
	texture->ddaX = old_x * cos(angle_radians) - old_y * sin(angle_radians);
	texture->ddaY = old_x * sin(angle_radians) + old_y * cos(angle_radians);
}

void	draw_game(t_data *texture)
{
	mlx_destroy_image(texture->mlx, texture->img);
	texture->img = mlx_new_image(texture->mlx, WIDTH, HEIGHT);
	put_background(texture);
	draw_wall(texture);
	put_minimap(texture);
	mlx_put_image_to_window(texture->mlx, texture->win, texture->img, 0, 0);
}
