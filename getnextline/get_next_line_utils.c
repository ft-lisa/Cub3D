/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 11:22:35 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/26 11:15:21 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check(char *src)
{
	int	t;

	t = 0;
	if (!src)
		return (0);
	while (src[t] != '\0')
	{
		if (src[t] == '\n')
			return (t);
		t++;
	}
	return (0);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void	*ft_replace(char *src)
{
	int		i;
	int		j;
	int		k;
	char	*new;

	i = 0;
	j = 0;
	k = 0;
	while (src[i] != 0 && src[i] != '\n')
		i++;
	while (src[j] != 0)
		j++;
	new = malloc(j - i + 1);
	if (!new)
		return (NULL);
	new[j - i++] = '\0';
	if (j - i != 0)
	{
		while (j > i + k)
		{
			new[k] = src[k + i];
			k++;
		}
	}
	return (new[k] = 0, free(src), new);
}

char	*ft_strdup(const char *source)
{
	char	*dest;
	int		len;
	int		i;

	i = 0;
	len = 0;
	while (source[len] != '\0' && source[len] != '\n')
	{
		len++;
	}
	dest = malloc(len * sizeof(char) + 2);
	if (dest == NULL)
		return (NULL);
	while (source[i] != '\0' && source[i] != '\n')
	{
		dest[i] = source[i];
		i++;
	}
	dest[i] = source[i];
	i++;
	dest[i] = '\0';
	return (dest);
}

char	*ff_strjoin(char const *s1, char const *s2, int count)
{
	char	*join;
	int		i;
	int		t;

	i = 0;
	t = 0;
	join = malloc(ft_strlen(s1) + count * sizeof(char) + 1);
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (t < count)
	{
		join[i] = s2[t];
		t++;
		i++;
	}
	join[i] = '\0';
	free((void *)s1);
	return (join);
}
