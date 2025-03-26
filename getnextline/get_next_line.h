/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:23:22 by lismarti          #+#    #+#             */
/*   Updated: 2025/03/26 11:12:20 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include "../cub3d.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
int		check(char *src);
size_t	ft_strlen(const char *str);
void	*ft_replace(char *src);
char	*ft_strdup(const char *source);
char	*ff_strjoin(char const *s1, char const *s2,int count);

#endif