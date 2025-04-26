/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lismarti <lismarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:07:10 by jaqin             #+#    #+#             */
/*   Updated: 2025/04/26 11:23:19 by lismarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	count_words(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] != c)
			count++;
		else if (str[i] == c && str[i + 1] && str[i + 1] != c)
			count++;
		i++;
	}
	return (count);
}

static void	free_all(char **split)
{
	int	word;

	word = 0;
	while (split[word])
	{
		free(split[word]);
		word++;
	}
	if (split)
		free(split);
}

static int	split_word(char **split, const char *s, char c, int word)
{
	int	start;
	int	end;

	start = 0;
	end = 0;
	while (s[end])
	{
		if (s[end] == c || s[end] == 0)
			start = end + 1;
		if (s[end] != c && (s[end + 1] == c || s[end + 1] == 0))
		{
			split[word] = malloc(sizeof(char) * (end - start + 2));
			if (!split[word])
				return (free_all(split), -1);
			ft_strlcpy(split[word], s + start, end - start + 2);
			word++;
		}
		end++;
	}
	split[word] = 0;
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**split;
	int		count;

	count = count_words(s, c);
	split = malloc(sizeof(char *) * (count + 1));
	if (!split)
		return (NULL);
	if (split_word(split, s, c, 0) == -1)
		return (NULL);
	return (split);
}
/* 
int	main(void)
{
	int	i = 0;
	char **split = ft_split("", ' ');
	// char **split = ft_split(".....test  la.fonction......", '.');
	//printf("%d\n", count_words("test  la fonction  ", ' '));
	//printf("%d\n", count_words(".....test  la.fonction......", '.')); 5  12
	// while (split[i])
	// 	printf("%s\n", split[i++]);

	//ft_split("xxxxxxxxhello!", 120:'x')
}
 */
