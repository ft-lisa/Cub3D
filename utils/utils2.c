/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 15:50:09 by lismarti          #+#    #+#             */
/*   Updated: 2025/05/03 12:40:41 by lismarti         ###   ########.fr       */
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

int	ft_atoi(const char *theString)
{
	int	i;
	int	num;
	int	signe;

	i = 0;
	num = 0;
	signe = 1;
	while ((theString[i] > 8 && theString[i] < 14) || theString[i] == 32)
		i++;
	if (theString[i] == 45)
		signe = -signe;
	if (theString[i] == 45 || theString[i] == 43)
		i++;
	while (theString[i] > 47 && theString[i] < 58)
	{
		num = num * 10 + theString[i] - 48;
		i++;
	}
	return (num * signe);
}
