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

int key_hook(int keycode)
{
    if (keycode == 32) // Barre d'espace pour démarrer
    {
        printf("Démarrage du jeu...\n");
        // Lancer ton jeu ici
    }
    return (0);
}

void display_mario_image(void *mlx, void *window)
{
    void *image;
    int width, height;

    // Charger l'image de Mario
    image = mlx_xpm_file_to_image(mlx, "game/mario_non.xpm", &width, &height);
    if (!image)
    {
        printf("Erreur lors du chargement de l'image.\n");
        exit(0);
    }

    // Afficher l'image sur la fenêtre
    mlx_put_image_to_window(mlx, window, image, 0, 0);
}

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
	display_mario_image(texture.mlx, texture.win);
	sleep(2);
	mlx_key_hook(texture.win, key_hook, NULL);
	//draw_game(&texture);
	mlx_hook(texture.win, 2, 1L << 0, key_press, &texture);   // Key down
	mlx_hook(texture.win, 3, 1L << 1, key_release, &texture); // Key up
	mlx_loop_hook(texture.mlx, update, &texture);             // Loop update
	mlx_loop(texture.mlx);
	return (0);
}
