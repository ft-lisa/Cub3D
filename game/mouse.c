#include "../cub3d.h"


void	mouse_rotate_view(t_data *data, float rot_speed)
{
	float	old_dirx;
	float	old_planex;

	old_dirx = data->dir_x;
	old_planex = data->plane_x;
	data->dir_x = data->dir_x * cos(rot_speed) - data->dir_y * sin(rot_speed);
	data->dir_y = old_dirx * sin(rot_speed) + data->dir_y * cos(rot_speed);
	data->plane_x = data->plane_x * cos(rot_speed) - \
	data->plane_y * sin(rot_speed);
	data->plane_y = old_planex * sin(rot_speed) + data->plane_y * cos(rot_speed);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		centerX;
	float	delta; // sensitivity factor

	(void)y;
	centerX = WIDTH / 2;
	delta = (x - centerX) * 0.002; // sensitivity factor
	if (delta != 0)
	{
		mouse_rotate_view(data, delta);
		// mlx_mouse_move(data->mlx, data->win, centerX, y); // recenter mouse
		mlx_mouse_move(data->mlx, data->win, WIDTH / 2, HEIGHT / 2); // recenter mouse
		mlx_mouse_hide(data->mlx, data->win);
	}
	return (0);
}