/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 11:39:03 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 12:05:58 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_texture_line(t_data *texture, t_ray* ray, t_tex* data)
{        
        if (ray->side == 0 && texture->x < ray->x)
        {
                data->tex = texture->west;
                data->texWidth = texture->widthwest;
                data->texHeight = texture->heightwest;
        }
        else if (ray->side == 0)
        {
                data->tex = texture->east;
                data->texWidth = texture->widtheast;
                data->texHeight = texture->heighteast;
        }
        if (ray->side == 1 && texture->y < ray->y)
        {
                data->tex = texture->south;
                data->texWidth = texture->widthsouth;
                data->texHeight = texture->heightsouth;
        }
        else if (ray->side == 1)
        {
                data->tex = texture->north;
                data->texWidth = texture->widthnorth;
                data->texHeight = texture->heightnorth;
        }
}

void init_calcul(t_data* texture, t_ray *ray, t_tex *data, int drawStart)
{
        data->lineHeight = HEIGHT / ray->perpWallDist;
        if (ray->side == 0)
                data->wallX = texture->y + ray->perpWallDist * texture->ddaY;
        else
                data->wallX = texture->x + ray->perpWallDist * texture->ddaX;
        data->wallX -= floor(data->wallX);
        data->texX = (int)(data->wallX * (double)data->texWidth);
        data->step = 1.0 * data->texHeight / (data->lineHeight);
        data->texPos = (drawStart - (-data->lineHeight / 2 + HEIGHT / 2)) * data->step;
        data->info = mlx_get_data_addr(data->tex, &data->bpp, &data->line_length, &data->endian);
        if (!data->info)
        {
                printf("Erreur : donnée de texture non valide !\n");
                free_data(texture);
        }
}

void	draw_texture_line(t_data *texture, t_ray *ray, int x)
{
        t_tex data;
        data.y = ray->draw_start;
        init_texture_line(texture, ray, &data);
        init_calcul(texture, ray, &data, ray->draw_start);
        while (data.y < ray->draw_end)
        {
                data.texY = (int)data.texPos;
                if (data.texY >= data.texHeight)
                        data.texY = data.texHeight - 1;
                if (data.texY < 0)
                        data.texY = 0;
                data.texPos += data.step;
                data.offset = data.texY * data.line_length + data.texX * (data.bpp / 8);
                if (data.texX < 0 || data.texX >= data.texWidth || data.texY < 0 || data.texY >= data.texHeight)
                {
                        break ;
                }
                data.color = *(unsigned int *)(data.info + data.offset);
                my_mlx_pixel_put(texture, x, data.y, data.color);
                data.y++;
        }
}
