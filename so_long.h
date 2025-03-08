/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 20:39:52 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/08 17:41:38 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H

# define SO_LONG_H
# include "get_next_line.h"
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
enum                    e_keycode
{
    ESC = 65307,
    KEY_DOWN = 65364,
    KEY_LEFT = 65361,
    KEY_RIGHT = 65363,
    KEY_UP = 65362,
};

typedef struct s_game
{
	int count;
	int x_exit;
	int y_exit;
	int w;
	int h;
	void *mlx;
	void *win;
	int		old_player_x;
	int		old_player_y;
	int		player_x;
	int		player_y;
	char	**o_map;
	int		player_count;
	int		collect_count;
	int		exit_count;
	void *wall;
	void *player;
	void *collect;
	void *exit;
	void *space;
	int		rows;
	int		cols;
	char	**map;
}			t_game;
void	ft_putstr(char *str);
void	ft_putnbr(int n);
void	ft_printf(const char *str, ...);
void	create_img(t_game *game);
void	count_map(t_game *game);
int 	input(int key, t_game *game);
int    move_right(t_game *game);
int	move_left(t_game *game);
int	move_down(t_game *game);
int	move_up(t_game *game);
void	start_game(t_game *game);
int	change_places(t_game *game);
char 	**copy_map(char **map);
int 	game_in(t_game *game);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_realloc(void *ptr, int old_size, int new_size);
int			ft_strcmp(const char *s1, const char *s2);
void		free_map(char **map, int rows);
char		**store_map(int fd);
int			open_map_file(char *map);
int			check_for_ber(char *map);
int			validate_map_line(char *line);
int			check_for_data(t_game *game);
void		ft_free(char **ptr);
int			all_walls(char **map);
void		flood_fill(char **map, int y, int x);
int			chack_valid_path(t_game *game);
void ft_free_image(t_game *game);
void ft_free_resources(t_game *game);
void close_window(t_game *game);
#endif