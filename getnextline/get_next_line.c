/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:45:40 by lismarti          #+#    #+#             */
/*   Updated: 2025/04/03 16:17:20 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*freealt(char **sc)
{
	free(*sc);
	*sc = NULL;
	return (NULL);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*result;
	unsigned int	i;
	size_t			check;

	i = 0;
	if (((int)count < 0 && (int)size != 0) || ((int)count != 0
			&& (int)size < 0))
		return (NULL);
	if (count != 0)
	{
		check = size * count / count;
		if (check != size)
			return (NULL);
	}
	result = malloc(count * size);
	if (result == NULL)
		return (NULL);
	while (count * size > i)
	{
		result[i] = 0;
		i++;
	}
	return (result);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*src;
	int			count;

	count = 1;
	buffer = malloc(BUFFER_SIZE);
	if (fd == -1)
		freealt(&src);
	if (!buffer)
		return (NULL);
	if (!src)
		src = ft_calloc(1, 1);
	while (check(src) == 0 && count > 0)
	{
		count = read(fd, buffer, BUFFER_SIZE);
		if (count <= 0)
			break ;
		src = ff_strjoin(src, buffer, count);
		if (!src)
			return (free(buffer), freealt(&src));
	}
	if (count < 0 || (!src[0] && count == 0))
		return (free(buffer), freealt(&src));
	src = ft_replace(src);
	return (free(buffer), ft_strdup(src));
}

// 7 max en -

//  #include <fcntl.h>
// #include <stdio.h>

// int	main(void)
// {
// 	int fd;
// 	char *str;
// 	fd =  -1;//open ("read_error.txt", O_RDONLY);
// 	// if (fd == -1) {
//     //     perror("Erreur lors de l'ouverture du fichier");
// 	// }
// 	str = get_next_line(fd);
// 	printf ("line 1:%s",str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf ("line 2:%s",str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf ("line 3:%s",str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf ("line 4:%s",str);
// 	free(str);
// 	str = get_next_line(fd);
// 	printf ("line 5:%s",str);
// 	free(str);
// } 
