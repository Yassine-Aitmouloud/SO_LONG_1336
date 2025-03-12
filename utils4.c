/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:46:32 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/12 02:33:55 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_for_pce(t_game *game)
{
	if (game->player_count != 1 || game->collect_count == 0
		|| game->exit_count != 1)
	{
		write(2, "Error\nYou need one P one E and some Cs", 39);
		return (0);
	}
	return (1);
}

size_t	count_lines(const char *filename)
{
	size_t	count;
	char	*line;
	int		fd;

	count = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nThere is no file", 11);
		return (0);
	}
	line = get_next_line(fd);
	while (line != NULL)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	count_map(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((game)->map[i])
	{
		j = 0;
		while ((game)->map[i][j])
			j++;
		i++;
	}
	(game)->rows = i;
	(game)->cols = j;
}

char	**copy_map(char **map, char *av)
{
	int		i;
	int		map_size;
	char	**o_map;

	map_size = count_lines(av);
	i = 0;
	o_map = malloc(sizeof(char *) * (map_size + 1));
	if (!o_map)
		return (NULL);
	while (map[i])
	{
		o_map[i] = ft_strdup(map[i]);
		if (!o_map[i])
		{
			free_map(o_map, i);
			free_map(map, i);
			return (NULL);
		}
		i++;
	}
	o_map[i] = NULL;
	return (o_map);
}

void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == 'E')
		map[y][x] = '1';
	if (y < 0 || x < 0 || !map[y] || !map[y][x] || map[y][x] == '1'
		|| map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
}
