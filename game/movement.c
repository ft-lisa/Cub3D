#include "../cub3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65307) // ESC
		exit(0);
	if (keycode == 119)
		data->w = 1;
	if (keycode == 115)
		data->s = 1;
	if (keycode == 97)
		data->a = 1;
	if (keycode == 100)
		data->d = 1;
	if (keycode == 65361)
		data->left = 1;
	if (keycode == 65363)
		data->right = 1;
	return (0);
}

// key release
int	key_release(int keycode, t_data *data)
{
	if (keycode == 119)
		data->w = 0;
	if (keycode == 115)
		data->s = 0;
	if (keycode == 97)
		data->a = 0;
	if (keycode == 100)
		data->d = 0;
	if (keycode == 65361)
		data->left = 0;
	if (keycode == 65363)
		data->right = 0;
	return (0);
}

int	update(t_data *data)
{
	float	moveSpeed;
	double	oldDirX;
	int	x;
	int	y;

	oldDirX = data->dirX;
	moveSpeed = 0.015;
	// Rotation
	if (data->left)
	{
		data->dirX = data->dirX * cos(-moveSpeed) - data->dirY
			* sin(-moveSpeed);
		data->dirY = oldDirX * sin(-moveSpeed) + data->dirY * cos(-moveSpeed);
		data->planeX = -data->dirY * 0.66;
		data->planeY = data->dirX * 0.66;
	}
	if (data->right)
	{
		data->dirX = data->dirX * cos(moveSpeed) - data->dirY * sin(moveSpeed);
		data->dirY = oldDirX * sin(moveSpeed) + data->dirY * cos(moveSpeed);
		data->planeX = -data->dirY * 0.66;
		data->planeY = data->dirX * 0.66;
	}
	// Déplacement du joueur
	if (data->w && dda(data) > 4)
	{
		x = data->x + data->dirX * moveSpeed;
		y = data->y + data->dirY * moveSpeed;
		if (data->game_map[y][x] != '1')
		{
			data->x += data->dirX * moveSpeed;
			data->y += data->dirY * moveSpeed;
		}
	}
	data->ddaX = -data->ddaX;
	data->ddaY = -data->ddaY;
	if (data->s && dda(data) > 4)
	{
		x = data->x - data->dirX * moveSpeed;
		y = data->y - data->dirY * moveSpeed;
		if (data->game_map[y][x] != '1')
		{
			data->x -= data->dirX * moveSpeed;
			data->y -= data->dirY * moveSpeed;
		}
	}
	draw_game(data);
	return (0);
}

// int update(t_data *data)
// {
// 	// // Rotation a changer en vecteur
// 	if (data->left)
// 		data->angle -= 0.015;
// 	if (data->right)
// 		data->angle += 0.015;
// 	if (data->angle > 6 || data->angle < -6)
// 		data->angle = 0;

// 	// Déplacement
// 	if (data->w)
// 	{
// 		data->x += sin(data->angle) * 0.015;
// 		data->y += cos(data->angle) * 0.015;
// 	}
// 	if (data->s)
// 	{
// 		data->x -= sin(data->angle) * 0.015;
// 		data->y -= cos(data->angle) * 0.015;
// 	}
// 	draw_game(data);
// 	return (0);
// }

// if (data->a)
// {
// 	data->angle -= 0.015;
// 	if (data->angle < 0)
// 		data->angle += 2 * PI;
// 	data->x = cos(data->angle);
// 	data->y = sin(data->angle);
// }
// if (data->d)
// {
// 	data->angle += 0.015;
// 	if (data->angle > 2 * PI)
// 		data->angle -= 2 * PI;
// 	data->x = cos(data->angle);
// 	data->y = sin(data->angle);
// }