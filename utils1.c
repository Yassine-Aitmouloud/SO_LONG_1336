/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:26:38 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/11 20:20:52 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_for_data(t_game *game)
{
	int (i), (j);
	i = 0;
	j = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
				(*game).player_count++;
			if (game->map[i][j] == 'C')
				(*game).collect_count++;
			if (game->map[i][j] == 'E')
			{
				game->x_exit = j;
				game->y_exit = i;
				(*game).exit_count++;
			}
			j++;
		}
		i++;
	}
	if (check_for_pce(game) == 0)
		return (0);
	return (1);
}

void	find_player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	check_valid_path(t_game *game)
{
	int	rows;
	int	cols;

	rows = 0;
	cols = 0;
	while (game->map[rows])
	{
		rows++;
	}
	if (rows > 0)
		cols = ft_strlen(game->map[0]);
	find_player_position(game);
	flood_fill(game->map, game->player_y, game->player_x);
	if (check_for_ec(game, rows) == 0)
		return (0);
	return (1);
}

void	ft_free_image(t_game *game)
{
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->player)
		mlx_destroy_image(game->mlx, game->player);
	if (game->collect)
		mlx_destroy_image(game->mlx, game->collect);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
	if (game->space)
		mlx_destroy_image(game->mlx, game->space);
}

void	ft_free_resources(t_game *game)
{
	if (!game)
		return ;
	if (game->o_map)
	{
		free_map(game->o_map, game->rows);
	}
	if (game->map)
	{
		free_map(game->map, game->rows);
	}
	ft_free_image(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}
