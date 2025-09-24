/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaqin <jaqin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 13:20:39 by jaqin             #+#    #+#             */
/*   Updated: 2025/04/21 13:28:23 by jaqin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_joinnfree(char *str, char *buffer)
{
	char	*temp;

	temp = ft_strjoin_gnl(str, buffer);
	free(str);
	return (temp);
}

char	*fill_str(int fd, char *str)
{
	char	*buffer;
	int		bytes_read;

	if (!str)
		str = ft_calloc(1, 1);
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(str);
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = 0;
		str = ft_joinnfree(str, buffer);
		if (ft_strchr(str, '\n'))
			break ;
	}
	free(buffer);
	return (str);
}

char	*set_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] && str[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*set_static(char *str)
{
	int		i;
	int		j;
	char	*next_static;

	i = 0;
	j = 0;
	while (str[i] != '\n' && str[i])
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	next_static = ft_calloc(ft_strlen(str) - i + 1, sizeof(char));
	if (!next_static)
		return (NULL);
	i++;
	while (str[i])
		next_static[j++] = str[i++];
	next_static[j] = 0;
	free(str);
	return (next_static);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = fill_str(fd, str);
	if (!str)
		return (NULL);
	line = set_line(str);
	str = set_static(str);
	return (line);
}
/* 
int	main()
{
	char *src;
	int	fd = open("read_error.txt", O_RDONLY);
	src = get_next_line(fd);
	printf("%s", src);
	free (src);
	src = get_next_line(fd);
	printf("%s", src);
	free (src);
	src = get_next_line(fd);
	printf("%s", src);
	free (src);
	src = get_next_line(-1);
	printf("%s", src);
	free (src);
	src = get_next_line(60);
	printf("%s", src);
	free (src);
	src = get_next_line(100);
	printf("%s", src);
	free (src);
} */
