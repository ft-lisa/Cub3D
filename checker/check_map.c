#include "../cub3d.h"

int	check_up_down(int old_size, int size_line, char *map, int i)
{
	int	j;

	j = where_in_line(map, i);
	if (j > old_size)
		return (ERROR);
	if (i + size_line > (int)ft_strlen(map))
		return (ERROR);
	if (map[i - old_size] == ' ' || map[i - old_size] == '\n')
		return (ERROR);
	if (map[size_line + i] == ' ' || map[size_line + i] == '\n')
		return (ERROR);
	return (GOOD);
}

int	check_wall(char *map, int i)
{
	int	old_size;
	int	size_line;

	size_line = len_line(map, i);
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			old_size = size_line;
			size_line = len_line(map, i + 1);
		}
		if (map[i] == '0' || map[i] == 'N' || map[i] == 'S' || map[i] == 'W'
			|| map[i] == 'E')
		{
			if (i == 0)
				return (printf(ERR_WALL), ERROR);
			if (map[i + 1] == ' ' || map[i - 1] == ' ' || map[i + 1] == '\n'
				|| map[i - 1] == '\n')
				return (printf(ERR_WALL), ERROR);
			if (check_up_down(old_size + 1, size_line + 1, map, i) == ERROR)
				return (printf(ERR_WALL), ERROR);
		}
		i++;
	}
	return (GOOD);
}

int	void_line(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i++] == '\n')
		{
			while (map[i] == ' ')
				i++;
			if (map[i] == '\n')
				return (printf(ERR_EMPTY), ERROR);
		}
	}
	return (GOOD);
}

int	check_element_map(char *map)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'N' || map[i] == 'S' || map[i] == 'W' || map[i] == 'E')
			count++;
		else if (map[i] != ' ' && map[i] != '\n' && map[i] != '0'
			&& map[i] != '1')
			return (printf(ERR_CHAR), ERROR);
		i++;
	}
	if (count < 1)
		return (printf(ERR_SPAWN), ERROR);
	if (count > 1)
		return (printf(ERR_MULT_SPAWN), ERROR);
	return (GOOD);
}

void	check_map(t_data *info)
{
	char	*copy_map;

	copy_map = info->map;
	if (check_element_map(copy_map) == ERROR)
	{
		free(info->map);
		exit(EXIT_FAILURE);
	}
	if (void_line(copy_map) == ERROR)
	{
		free(info->map);
		exit(EXIT_FAILURE);
	}
	if (check_wall(copy_map, 0) == ERROR)
	{
		free(info->map);
		exit(EXIT_FAILURE);
	}
}
