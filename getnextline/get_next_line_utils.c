/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqin <jaqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 17:38:22 by jaqin             #+#    #+#             */
/*   Updated: 2025/04/21 13:00:27 by jaqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		count++;
		s++;
	}
	return (count);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	i = 0;
	if (siz <= 0)
		return (ft_strlen(src));
	while (i < siz - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src));
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*array;
	size_t	i;

	if (size != 0 && ((nmemb * size) / size != nmemb))
		return (NULL);
	i = 0;
	array = malloc(size * nmemb);
	if (!array)
		return (NULL);
	while (i < nmemb * size)
	{
		((unsigned char *)array)[i] = 0;
		i++;
	}
	return (array);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (unsigned char)c)
			return (&((char *)s)[i]);
		i++;
	}
	if (s[i] == (unsigned char)c)
		return (&((char *)s)[i]);
	return (NULL);
}

char	*ft_strjoin_gnl(char const *s1, char const *s2)
{
	size_t	s1len;
	size_t	s2len;
	char	*join;

	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	join = (char *)malloc(sizeof(char) * (s1len + s2len + 1));
	if (!join || !s1 || !s2)
		return (NULL);
	ft_strlcpy(join, s1, s1len + 1);
	ft_strlcpy(join + s1len, s2, s2len + 1);
	return (join);
}
/* 
char	*ft_strjoin(char *s1, char *s2)
{
	char	*start;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	start = str;
	while (*s1)
		*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (start);
}
 */
