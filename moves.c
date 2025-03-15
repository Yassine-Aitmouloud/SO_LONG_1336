/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 20:21:40 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/13 02:21:17 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	move_left(t_game *game)
{
	int (i), (j);
	j = game->player_x;
	i = game->player_y;
	if (j - 1 == game->x_exit && i == game->y_exit && game->collect_count == 0)
	{
		ft_printf("count = %d\n", game->count);
		ft_printf(">>>>>>>>>>>>>>>>>You won<<<<<<<<<<<<<<<<\n");
		close_window(game);
	}
	if (game->o_map[i][j - 1] != '1' && game->o_map[i][j - 1] != 'E')
	{
		if (game->o_map[i][j - 1] == 'C')
			game->collect_count--;
		game->o_map[i][j] = '0';
		game->old_player_y = i;
		game->old_player_x = j;
		game->o_map[i][j - 1] = 'P';
		game->player_y = i;
		game->player_x = j - 1;
	}
	else
		return (0);
	if (!change_places(game))
		return (0);
	return (1);
}

int	move_right(t_game *game)
{
	int (i), (j);
	j = game->player_x;
	i = game->player_y;
	if (j + 1 == game->x_exit && i == game->y_exit && game->collect_count == 0)
	{
		ft_printf("count = %d\n", game->count);
		ft_printf(">>>>>>>>>>>>>>>>>You won<<<<<<<<<<<<<<<<\n");
		close_window(game);
	}
	if (game->o_map[i][j + 1] != '1' && game->o_map[i][j + 1] != 'E')
	{
		if (game->o_map[i][j + 1] == 'C')
			game->collect_count--;
		game->o_map[i][j] = '0';
		game->old_player_y = i;
		game->old_player_x = j;
		game->o_map[i][j + 1] = 'P';
		game->player_y = i;
		game->player_x = j + 1;
	}
	else
		return (0);
	if (!change_places(game))
		return (0);
	return (1);
}

int	move_down(t_game *game)
{
	int (i), (j);
	j = game->player_x;
	i = game->player_y;
	if (j == game->x_exit && i + 1 == game->y_exit && game->collect_count == 0)
	{
		ft_printf("count = %d\n", game->count);
		ft_printf(">>>>>>>>>>>>>>>>>You won<<<<<<<<<<<<<<<<\n");
		close_window(game);
	}
	if (game->o_map[i + 1][j] != '1' && game->o_map[i + 1][j] != 'E')
	{
		if (game->o_map[i + 1][j] == 'C')
			game->collect_count--;
		game->o_map[i][j] = '0';
		game->old_player_y = i;
		game->old_player_x = j;
		game->o_map[i + 1][j] = 'P';
		game->player_y = i + 1;
		game->player_x = j;
	}
	else
		return (0);
	if (!change_places(game))
		return (0);
	return (1);
}

int	move_up(t_game *game)
{
	int (i), (j);
	j = game->player_x;
	i = game->player_y;
	if (j == game->x_exit && i - 1 == game->y_exit && game->collect_count == 0)
	{
		ft_printf("count = %d\n", game->count);
		ft_printf(">>>>>>>>>>>>>>>>>You won<<<<<<<<<<<<<<<<\n");
		close_window(game);
	}
	if (game->o_map[i - 1][j] != '1' && game->o_map[i - 1][j] != 'E')
	{
		if (game->o_map[i - 1][j] == 'C')
			game->collect_count--;
		game->o_map[i][j] = '0';
		game->old_player_y = i;
		game->old_player_x = j;
		game->o_map[i - 1][j] = 'P';
		game->player_y = i - 1;
		game->player_x = j;
	}
	else
		return (0);
	if (!change_places(game))
		return (0);
	return (1);
}

int	game_in(t_game *game)
{
	game->mlx = mlx_init();
	count_map(game);
	if (!game->mlx)
	{
		ft_free_resources(game);
		write(2, "Error\nmlx", 9);
		return (0);
	}
	create_img(game);
	game->win = mlx_new_window(game->mlx, game->cols * 64, game->rows * 64,
			"so_long");
	if (!game->win)
	{
		write(2, "Error\nwin", 9);
		ft_free_resources(game);
		return (0);
	}
	start_game(game);
	mlx_key_hook(game->win, input, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
	free(game->mlx);
	return (1);
}
