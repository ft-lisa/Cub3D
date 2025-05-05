/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:39:03 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/03 12:26:23 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_texture_line(t_data *texture, t_ray *ray, t_tex *data)
{
	if (ray->side == 0 && texture->x < ray->x)
	{
		data->tex = texture->east;
		data->tex_width = texture->widtheast;
		data->tex_height = texture->heighteast;
	}
	else if (ray->side == 0)
	{
		data->tex = texture->west;
		data->tex_width = texture->widthwest;
		data->tex_height = texture->heightwest;
	}
	if (ray->side == 1 && texture->y < ray->y)
	{
		data->tex = texture->south;
		data->tex_width = texture->widthsouth;
		data->tex_height = texture->heightsouth;
	}
	else if (ray->side == 1)
	{
		data->tex = texture->north;
		data->tex_width = texture->widthnorth;
		data->tex_height = texture->heightnorth;
	}
}

void	init_calcul(t_data *texture, t_ray *ray, t_tex *data, int drawStart)
{
	data->line_height = HEIGHT / ray->perpwalldist;
	if (ray->side == 0)
		data->wall_x = texture->y + ray->perpwalldist * texture->dda_y;
	else
		data->wall_x = texture->x + ray->perpwalldist * texture->dda_x;
	data->wall_x -= floor(data->wall_x);
	data->tex_x = (int)(data->wall_x * (double)data->tex_width);
	data->step = 1.0 * data->tex_height / (data->line_height);
	data->tex_pos = (drawStart - (-data->line_height / 2 + HEIGHT / 2))
		* data->step;
	data->info = mlx_get_data_addr(data->tex, &data->bpp, &data->line_length,
			&data->endian);
	if (!data->info)
	{
		printf("Erreur : donnée de texture non valide !\n");
		texture->value = 1;
		free_data(texture);
	}
}

void	draw_texture_line(t_data *texture, t_ray *ray, int x)
{
	t_tex	data;

	data.y = ray->draw_start;
	init_texture_line(texture, ray, &data);
	init_calcul(texture, ray, &data, ray->draw_start);
	while (data.y < ray->draw_end)
	{
		data.tex_y = (int)data.tex_pos;
		if (data.tex_y >= data.tex_height)
			data.tex_y = data.tex_height - 1;
		if (data.tex_y < 0)
			data.tex_y = 0;
		data.tex_pos += data.step;
		data.offset = data.tex_y * data.line_length;
		data.offset += data.tex_x * (data.bpp / 8);
		if (data.tex_x < 0 || data.tex_x >= data.tex_width || data.tex_y < 0
			|| data.tex_y >= data.tex_height)
		{
			break ;
		}
		data.color = *(unsigned int *)(data.info + data.offset);
		my_mlx_pixel_put(texture, x, data.y, data.color);
		data.y++;
	}
}
