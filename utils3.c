/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:34:03 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/12 03:57:56 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	validate_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != '1' && line[i] != '0' && line[i] != 'P' && line[i] != 'E'
			&& line[i] != 'C')
		{
			write(2, "Error\nYou can use '1' '0' 'C' 'E' 'P'", 37);
			return (0);
		}
		i++;
	}
	return (1);
}

void	ft_free(char **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

int	all_walls(char **map)
{
	int (i), (j) = {0};
	while (map[0][j])
	{
		if (map[0][j] != '1')
			return (0);
		j++;
	}
	i = 0;
	while (map[i])
	{
		if (map[i][0] != '1' || map[i][ft_strlen(map[i]) - 1] != '1')
			return (0);
		i++;
	}
	i--;
	j = 0;
	while (map[i][j])
	{
		if (map[i][j] != '1')
			return (0);
		j++;
	}
	return (1);
}

char *	ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}

char *get_filename(char *path)
{
    char *filename = ft_strrchr(path, '/');
	if (filename == NULL)
		return (path);
	return (filename + 1);
}

int check_for_ber(char *name)
{
    char *filename = get_filename(name);
    int len = ft_strlen(filename);
    if (len <= 4 || ft_strcmp(filename + len - 4, ".ber") != 0)
    {
        write(2, "Error\n.ber\n", 11);
        return 0;
    }

    return 1;
}
