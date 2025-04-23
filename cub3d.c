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

void	my_mlx_pixel_put(t_data *texture, int x, int y, int color)
{
	char	*dst;

	dst = texture->img_ptr + ((y * texture->line_length)
			+ (x * (texture->bits_per_pixel / 8)));
	*(unsigned int *)dst = color;
}

float ray_right(t_data* texture, t_ray ray)
{
	while(texture->game_map[ray.x][ray.y + ray.loop] != '1' && ray.x < texture->size_map && ray.y + ray.loop != '\0')
	{
		ray.x = (int)(texture->x + ray.loop * tan(texture->angle));
		ray.loop++;
	}
		
	ray.fx = texture->x + ray.loop * tan(texture->angle);
	ray.fy = ray.loop + ray.y;
	printf("DIS1 fut x : %f, fut y : %f\n\n", ray.fx, ray.fy);
	ray.distance = sqrt((ray.fx - texture->x) * (ray.fx - texture->x) + (ray.fy - texture->y) * (ray.fy - texture->y));
	return(ray.distance);
}

float ray_down(t_data* texture, t_ray ray)
{
	while(texture->game_map[ray.x + ray.loop][ray.y] != '1' && ray.x + ray.loop <= texture->size_map && ray.y!= '\0')
	{
		ray.y = (int)(texture->y + (ray.loop * cos(texture->angle)));
		ray.loop++;
	}	
	ray.fy = texture->y + ray.loop * cos(texture->angle);
	ray.fx = ray.loop + ray.x;
	printf("DIS2 fut x : %f, fut y : %f\n\n", ray.fx, ray.fy);
	ray.distance = sqrt((ray.fx - texture->x) * (ray.fx - texture->x) + (ray.fy - texture->y) * (ray.fy - texture->y));
	return(ray.distance);
}


float dda(t_data *texture)
{
	t_ray ray;

	ray.loop = 0;
	ray.x = texture->x;
	ray.y = texture->y;
	ray.distance2 = 0;
	
	if (texture->angle < PI / 3 && texture->angle > -(PI / 3))
		ray.distance = ray_right(texture, ray);
	if (texture->angle < ((5 * PI) / 6) && texture->angle > (PI / 4))
		ray.distance = ray_down(texture, ray);
	if (texture->angle < PI / 3 && texture->angle > -(PI / 3))
 	printf("dis1 : %f dis2 : %f\n", ray.distance, ray.distance2);
	return(ray.distance);


	// loop = 0;
	// while(texture->game_map[x + loop][y] != '1') // on va vers le haut en décrémentant Y
	// {
	//     y = (int)(texture->y + loop * tan(texture->angle));
	//     loop++;
	// }
	
	// fy = texture->y + loop * tan(texture->angle);
	// fx = x - loop;  // On décrémente Y pour aller vers le haut
	// distance2 = sqrt((fx - texture->x) * (fx - texture->x) + (fy - texture->y) * (fy - texture->y));
	
	// if (distance < distance2)
	
	
	//printf("x: %f, y: %f loop: %d, futur x: %f, cos angle : %f, dis : %f\n", texture->x, texture->y, loop, fx, sin(texture->angle), distance);
	// return(distance2);
}


void	line(t_data *texture)
{

	double angle = texture->angle;
	int i = 0;
	int length = 50; //dda(texture) * 32; 
	printf("ang : %f\n", texture->angle);

	int start_x = texture->y * 32 + 4; 
	int start_y = texture->x * 32  + 4;

	while (i < length)
	{
		int px = start_x + cos(angle) * i;
		int py = start_y + sin(angle) * i;
		// mlx_pixel_put(texture->mlx, texture->win, px, py, 0xFF0000);
		my_mlx_pixel_put(texture, px, py, 0xFF0000);
		i++;
	}
}


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
			// mlx_pixel_put(texture->mlx, texture->win, texture->y * 32 + l,texture->x * 32 + k,  16776960);
			my_mlx_pixel_put(texture, texture->y * 32 + l,texture->x * 32 + k,  16776960);
			l++;
		}
		k++;
	}
	line(texture);
}

void put_square(t_data *texture, char lettre, int i, int j)
{
	int color;
	int k;
	int l;
	int size;


	k = 0;
	size = 32;
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
			// mlx_pixel_put(texture->mlx, texture->win, j * 32 + l, i * 32 + k, color);
			my_mlx_pixel_put(texture, j * 32 + l, i * 32 + k, color);
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
	// mlx_clear_window(texture->mlx, texture->win);
	if (texture->mlx && texture->img)  // a tester si vraiment besoin
	{
		mlx_destroy_image(texture->mlx, texture->img);
		texture->img = NULL;
	}
	texture->img = mlx_new_image(texture->mlx, 1366, 768);
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
	mlx_put_image_to_window(texture->mlx, texture->win, texture->img, 0, 0);
}

int key_press(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 119) data->w = 1;  
	if (keycode == 115) data->s = 1;     
	if (keycode == 97)  data->a = 1;     
	if (keycode == 100) data->d = 1;  
	if (keycode == 65361) data->left = 1;  
	if (keycode == 65363) data->right = 1;  
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
	if (data->left)
		data->angle -= 0.005;
  //changer car si on le fait a l'infini on a overflow utiliser pi
	if (data->right)
		data->angle += 0.005;
	if (data->angle > 6 || data->angle < -6)
		data->angle = 0;

	// Déplacement
	if (data->w)
	{
		data->x += sin(data->angle) * 0.005;
		data->y += cos(data->angle) * 0.005;
	}
	if (data->s)
	{
		data->x -= sin(data->angle) * 0.005;
		data->y -= cos(data->angle) * 0.005;
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
        //print_data(&texture);
	start_minimap(&texture);
	mlx_hook(texture.win, 2, 1L<<0, key_press, &texture);    // Key down
	mlx_hook(texture.win, 3, 1L<<1, key_release, &texture);  // Key up
	mlx_loop_hook(texture.mlx, update, &texture);           // Loop update
	mlx_loop(texture.mlx);
        return(0);
}
