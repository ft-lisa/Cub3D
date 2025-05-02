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
