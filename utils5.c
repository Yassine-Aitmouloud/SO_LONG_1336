/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:18:59 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/11 21:14:18 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_for_ec(t_game *game, int rows)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E' || game->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

void	put_images(t_game *game, int i, int j)
{
	if (game->o_map[i][j] == '1')
		mlx_put_image_to_window(game->mlx, game->win, game->wall, j * 64, i
			* 64);
	else if (game->o_map[i][j] == 'P')
		mlx_put_image_to_window(game->mlx, game->win, game->player, j * 64, i
			* 64);
	else if (game->o_map[i][j] == 'C')
		mlx_put_image_to_window(game->mlx, game->win, game->collect, j * 64, i
			* 64);
	else if (game->o_map[i][j] == 'E')
		mlx_put_image_to_window(game->mlx, game->win, game->exit, j * 64, i
			* 64);
	else
		mlx_put_image_to_window(game->mlx, game->win, game->space, j * 64, i
			* 64);
}

void	free_maps(t_game *game)
{
	ft_free(game->map);
	ft_free(game->o_map);
}

void	start_game(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->o_map[i])
	{
		j = 0;
		while (game->o_map[i][j])
		{
			put_images(game, i, j);
			j++;
		}
		i++;
	}
}

int	change_places(t_game *game)
{
	int	i;
	int	j;

	i = game->player_y;
	j = game->player_x;
	if (game->o_map[i][j] == 'P')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->player,
			game->player_x * 64, game->player_y * 64);
		mlx_put_image_to_window(game->mlx, game->win, game->space,
			game->old_player_x * 64, game->old_player_y * 64);
		return (1);
	}
	return (0);
}
