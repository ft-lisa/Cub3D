#include "cub3d.h"
#include <stdio.h>

void	free_game_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	free_data(t_data *game)
{
	(void)game;
	if (game->map)
		free(game->map);
	if (game->game_map)
		free_game_map(game->game_map);
	if (game->north)
		mlx_destroy_image(game->mlx, game->north);
	if (game->south)
		mlx_destroy_image(game->mlx, game->south);
	if (game->east)
		mlx_destroy_image(game->mlx, game->east);
	if (game->west)
		mlx_destroy_image(game->mlx, game->west);
	if (game->img)
		mlx_destroy_image(game->mlx, game->img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
	return (1);
}

// void print_game_data(t_data *game)
// {
//     // Affichage des informations de la carte
//     printf("Map: %s\n", game->map);
//     printf("Size of map: %d\n", game->size_map);

//     // Affichage des images
//     printf("North texture: %p\n", game->north);
//     printf("South texture: %p\n", game->south);
//     printf("East texture: %p\n", game->east);
//     printf("West texture: %p\n", game->west);

//     // Affichage des informations de la fenêtre et mlx
//     printf("MLX pointer: %p\n", game->mlx);
//     printf("Window pointer: %p\n", game->win);

//     // Affichage des informations de l'image
//     printf("Image pointer: %p\n", game->img);
//     printf("Image pointer (raw): %p\n", game->img_ptr);
//     printf("Bits per pixel: %d\n", game->bits_per_pixel);
//     printf("Line length: %d\n", game->line_length);
//     printf("Endian: %d\n", game->endian);

//     // Affichage des couleurs
//     printf("Floor color: %d\n", game->color_floor);
//     printf("Ceiling color: %d\n", game->color_ceilling);

//     // Affichage des informations sur le joueur
//     printf("Player position (x, y): %.2f, %.2f\n", game->x, game->y);
//     printf("Player direction (dirX, dirY): %.2f, %.2f\n", game->dirX,
// 	game->dirY);
//     printf("Player DDA (ddaX, ddaY): %.2f, %.2f\n", game->ddaX, game->ddaY);
//     printf("Player plane (planeX, planeY): %.2f, %.2f\n", game->planeX,
// 	game->planeY);
//     printf("Player angle: %.2f\n", game->angle);

//     // Affichage des touches
//     printf("Key W: %d\n", game->w);
//     printf("Key S: %d\n", game->s);
//     printf("Key A: %d\n", game->a);
//     printf("Key D: %d\n", game->d);
//     printf("Key Left: %d\n", game->left);
//     printf("Key Right: %d\n", game->right);
// }

int	display_mario_image(void *mlx, void *window)
{
	void	*image;
	int		width;
	int		height;

	image = mlx_xpm_file_to_image(mlx, "game/mario_non.xpm", &width, &height);
	if (!image)
	{
		printf("Erreur lors du chargement de l'image.\n");
		return (0);
	}
	mlx_put_image_to_window(mlx, window, image, width / 2 + 180, height / 2);
    mlx_destroy_image(mlx, image);
	return (1);
}


// voir pour getnext_line
// bien verifier l'orientation des textures
// message dans sortie d'erreur ? mettre error ?

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
	mlx_hook(texture.win, 2, 1L << 0, key_press, &texture);
	mlx_hook(texture.win, 3, 1L << 1, key_release, &texture);
	mlx_hook(texture.win, DestroyNotify, StructureNotifyMask, free_data,
		&texture);
	mlx_loop_hook(texture.mlx, update, &texture);
	mlx_loop(texture.mlx);
	return (0);
}
