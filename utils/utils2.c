/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:50:09 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/02 15:50:10 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	len_line(char *map, int i)
{
	int	k;

	k = 0;
	while (map[i + k] != '\n' && map[i + k] != '\0')
		k++;
	return (k);
}

int	where_in_line(char *map, int i)
{
	int	k;

	k = 0;
	while (map[i - k] != '\n' && i - k >= 0)
		k++;
	return (k);
}
