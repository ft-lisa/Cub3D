#include "cub3d.h"

char* pass_space(char* line)
{
        while(*line != '\0' && *line == ' ')
                line++;
        return(line);
}

int pass_element(t_element* map)
{
        if (map->c == 1 && map->f == 1)
        {
                if (map->no == 1 && map->so == 1 && map->ea == 1 && map->we == 1)
                        return(GOOD);
        }
        return(ERROR);               
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	int		i;
	int		t;

	i = 0;
	t = 0;
        if (s1 == NULL)
                return(ft_strdup(s2));
        if (s2 == NULL)
                return(ft_strdup(s1));
	join = malloc(ft_strlen(s1) + ft_strlen(s2) * sizeof(char) + 1);
	if (join == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[t] != '\0')
	{
		join[i] = s2[t];
		t++;
		i++;
	}
	join[i] = '\0';
	free((void *)s1);
	return (join);
}