/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:35:12 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/11 21:53:13 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**allocate_map(t_helper *helper)
{
	helper->line = get_next_line(helper->fd);
	while (helper->line != NULL)
	{
		if (helper->j == 0)
			helper->j = ft_strlen(helper->line);
		else if (ft_strlen(helper->line) != helper->j)
		{
			free(helper->line);
			helper->line = get_next_line(-1);
			free(helper->line);
			free_map(helper->map, helper->i);
			close(helper->fd);
			return (NULL);
		}
		helper->map[helper->i] = helper->line;
		helper->i++;
		helper->line = get_next_line(helper->fd);
	}
	helper->map[helper->i] = NULL;
	close(helper->fd);
	return (helper->map);
}

char	**store_map(char *filename)
{
	t_helper	helper;

	helper.i = 0;
	helper.j = 0;
	helper.fd = open(filename, O_RDONLY);
	if (helper.fd == -1)
	{
		write(2, "Error\nopen\n", 11);
		return (NULL);
	}
	helper.map_size = count_lines(filename);
	if (helper.map_size == 0)
	{
		write(2, "Error\nempty file\n", 17);
		close(helper.fd);
		return (NULL);
	}
	helper.map = (char **)malloc(sizeof(char *) * (helper.map_size + 1));
	if (!helper.map)
	{
		write(2, "Error\nmalloc\n", 13);
		close(helper.fd);
		return (NULL);
	}
	return (allocate_map(&helper));
}

void	get_the_map(int ac, char **av, t_game *game)
{
	if (ac != 2)
	{
		write(2, "Error\nThere is no map", 23);
		exit(0);
	}
	if (check_for_ber(av[1]) == 0)
		exit(0);
	game->map = store_map(av[1]);
	if (game->map == NULL)
	{
		ft_free_resources(game);
		write(2, "Error\nThe map must be rectangular ", 35);
		exit(0);
	}
	game->o_map = copy_map(game->map, av[1]);
}

void	validate_map(t_game *game)
{
	int (i) = 0;
	while (game->map[i])
	{
		if (validate_map_line(game->map[i]) == 0)
		{
			free_maps(game);
			exit(0);
		}
		i++;
	}
	if (all_walls(game->map) == 0)
	{
		free_maps(game);
		write(2, "Error\nThe map must be enclosed/surrounded by walls", 51);
		exit(0);
	}
	if (check_for_data(game) == 0)
	{
		free_maps(game);
		exit(0);
	}
	game->rows = i;
}

int	main(int ac, char **av)
{
	t_game	game;

	game = (t_game){0};
	game.count = 1;
	get_the_map(ac, av, &game);
	validate_map(&game);
	if (check_valid_path(&game) == 0)
	{
		write(2, "Error\nThere is no way to win", 29);
		ft_free_resources(&game);
		exit(0);
	}
	if (!game_in(&game))
	{
		ft_free_resources(&game);
		return (0);
	}
	ft_free_resources(&game);
	return (1);
}
