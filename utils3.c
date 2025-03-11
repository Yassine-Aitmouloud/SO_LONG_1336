/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:34:03 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/11 19:40:06 by yaaitmou         ###   ########.fr       */
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
			write(2, "Err3r\n", 6);
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

int	check_for_ber(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len <= 4 || ft_strcmp(name + len - 4, ".ber") != 0)
	{
		write(2, "Error\n.ber", 10);
		return (0);
	}
	return (1);
}
