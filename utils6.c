/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 21:16:42 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/11 21:53:28 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	create_img(t_game *game)
{
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &game->w,
			&game->h);
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm",
			&game->w, &game->h);
	game->collect = mlx_xpm_file_to_image(game->mlx, "textures/coin.xpm",
			&game->w, &game->h);
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &game->w,
			&game->h);
	game->space = mlx_xpm_file_to_image(game->mlx, "textures/space.xpm",
			&game->w, &game->h);
	if (!game->wall || !game->player || !game->collect || !game->exit
		|| !game->space)
	{
		ft_free_resources(game);
		write(2, "Error\nimages_not_found", 22);
		exit(0);
	}
}

int	input(int key, t_game *game)
{
	if (key == ESC)
		close_window(game);
	else if (key == 17)
		close_window(game);
	else if (key == 119)
	{
		if (move_up(game))
			ft_printf("count = %d\n", game->count++);
	}
	else if (key == 115)
	{
		if (move_down(game))
			ft_printf("count = %d\n", game->count++);
	}
	else if (key == 97)
	{
		if (move_left(game))
			ft_printf("count = %d\n", game->count++);
	}
	else if (key == 100)
	{
		if (move_right(game))
			ft_printf("count = %d\n", game->count++);
	}
	return (0);
}
