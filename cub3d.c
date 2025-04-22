#include "cub3d.h"

#include <stdio.h>

#include <stdio.h>

void	print_data(t_data *data)
{
	int i = 0;

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


/* voir le cas si il y a des espaces derriere est de que il faut prendre e ncompte que toutes les lignes on la meme taille */

// void	my_mlx_pixel_put(t_fractal *fractal, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = fractal->img_ptr + ((y * fractal->line_length)
// 			+ (x * (fractal->bits_per_pixel / 8)));
// 	*(unsigned int *)dst = color;
// }

void	put_character(t_data *texture)
{
	int k;
	int l;
	int size;

	k = 0;
	l = 0;
	size = 8;
	while(k < size)
	{
		l = 0;
		while(l < size)
		{
			mlx_pixel_put(texture->mlx, texture->win, texture->y * 32 + l + 10,texture->x * 32 + k +10,  16776960);
			l++;
		}
		k++;
	}
}

void put_square(t_data *texture, char lettre, int i, int j)
{
	int color;
	int k;
	int l;
	int size;


	k = 0;
	size = 28;
	if (lettre == '0')
		color = 0;
	else if (lettre == '1')
		color = 654654;
	else 
		return ;
	while(k < size)
	{
		l = 0;
		while(l < size)
		{
			mlx_pixel_put(texture->mlx, texture->win, j * 32 + l, i * 32 + k, color);
			l++;
		}
		k++;
	}
}

void start_minimap(t_data* texture)
{
	int	i;
	int	j;

	i = 0;
	mlx_clear_window(texture->mlx, texture->win);
	while (texture->game_map[i])
	{
		j = 0;
		while (texture->game_map[i][j])
		{
				put_square(texture, texture->game_map[i][j], i, j);
			j++;
		}
		i++;
	}
	put_character(texture);
}

int	key_hook(int keycode, t_data *texture)
{
	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == W || keycode == UP) // W
		texture->x -= 0.1;
	if (keycode == S || keycode == DOWN) // S
		texture->x += 0.1;
	if (keycode == A || keycode == LEFT) // A
		texture->y -= 0.1;
	if (keycode == D || keycode == RIGHT) // D
		texture->y += 0.1;

	mlx_clear_window(texture->mlx, texture->win);
	start_minimap(texture);
	return (0);
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 119) data->w = 1;     // W
	if (keycode == 115) data->s = 1;     // S
	if (keycode == 97)  data->a = 1;     // A
	if (keycode == 100) data->d = 1;     // D
	if (keycode == 65361) data->left = 1;   // Left
	if (keycode == 65363) data->right = 1;  // Right
	return (0);
}

// key release
int key_release(int keycode, t_data *data)
{
	if (keycode == 119) data->w = 0;
	if (keycode == 115) data->s = 0;
	if (keycode == 97)  data->a = 0;
	if (keycode == 100) data->d = 0;
	if (keycode == 65361) data->left = 0;
	if (keycode == 65363) data->right = 0;
	return (0);
}

int update(t_data *data)
{
	// // Rotation
	// if (data->left)
	// 	data->angle -= data->angle;
	// if (data->right)
	// 	data->angle += data->angle;

	// Déplacement
	if (data->w)
	{
		data->x += cos(data->angle) * 0.001;
		data->y += sin(data->angle) * 0.001;
	}
	if (data->s)
	{
		data->x -= cos(data->angle) * 0.001;
		data->y -= sin(data->angle) * 0.001;
	}
	start_minimap(data);
	return (0);
}

int     main(int argc, char** argv)
{        
        t_data texture;

        if (argc != 2)
                return(printf(ERR_ARG), EXIT_FAILURE);
        if (check_element(argv[1]) == 0)
                return(EXIT_FAILURE);
        texture = init_list();
        fill_map(argv[1], &texture);
        check_map(&texture);
        fill_struct(&texture, argv[1]);
        print_data(&texture);
		start_minimap(&texture);
		// mlx_key_hook(texture.win, key_hook, &texture);
		mlx_hook(texture.win, 2, 1L<<0, key_press, &texture);    // Key down
		mlx_hook(texture.win, 3, 1L<<1, key_release, &texture);  // Key up
		mlx_loop_hook(texture.mlx, update, &texture);           // Loop update
		mlx_loop(texture.mlx);
        return(0);
}
