/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:48:10 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 16:03:45 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_element	init_element(void)
{
	t_element	element;

	element.c = 0;
	element.f = 0;
	element.no = 0;
	element.so = 0;
	element.ea = 0;
	element.we = 0;
	return (element);
}

void	init_list2(t_data *texture)
{
	texture->dir_x = 0;
	texture->dir_y = 0;
	texture->dda_x = 0;
	texture->dda_y = 0;
	texture->plane_x = 0;
	texture->plane_y = 0;
	texture->angle = (PI);
	texture->w = 0;
	texture->s = 0;
	texture->a = 0;
	texture->d = 0;
	texture->left = 0;
	texture->right = 0;
	texture->value = 0;
}

t_data	init_list(void)
{
	t_data	texture;

	texture.map = NULL;
	texture.north = NULL;
	texture.south = NULL;
	texture.east = NULL;
	texture.west = NULL;
	texture.mlx = NULL;
	texture.win = NULL;
	texture.color_ceilling = -1;
	texture.color_floor = -1;
	texture.x = 0;
	texture.y = 0;
	init_list2(&texture);
	return (texture);
}
