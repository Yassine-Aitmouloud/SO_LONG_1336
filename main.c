#include "get_next_line.h"
#include "so_long.h"

void	create_img(t_game *game)
{
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &game->w, &game->h);
	if (!game->wall)
	{
		write(2, "Error\nwall", 10);
		exit(0);
	}
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &game->w, &game->h);
	if (!game->player)
	{
		write(2, "Error\nplayer", 12);
		exit(0);
	}
	game->collect = mlx_xpm_file_to_image(game->mlx, "textures/coin.xpm", &game->w, &game->h);
	if (!game->collect)
	{
		write(2, "Error\ncollect", 13);
		exit(0);
	}
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &game->w, &game->h);
	if (!game->exit)
	{
		write(2, "Error\nexit", 11);
		exit(0);
	}
	game->space = mlx_xpm_file_to_image(game->mlx, "textures/space.xpm", &game->w, &game->h);
	if (!game->space)
	{
		write(2, "Error\nspace", 12);
		exit(0);
	}
}
char	**store_map(int fd)
{
	size_t		i;
	size_t		j;
	char	*line;
	char	**map;
	char	**tmp_map;
	size_t	map_size;

	i = 0;
	j = 0;
	map = NULL;
	map_size = 0;
	map = malloc(sizeof(char *) * 1);
	while ((line = get_next_line(fd)) != NULL)
	{
		if (j == 0)
			j = ft_strlen(line);
		else if (ft_strlen(line) != j)
		{
			write(2, "Erro1\n", 6);
			free(line);
			free_map(map, i);
			return (NULL);
		}
		tmp_map = ft_realloc(map, sizeof(char *) * map_size, sizeof(char *) * (i
					+ 2));
		if (!tmp_map)
		{
			write(2, "Erro2\n", 6);
			free(line);
			free_map(map, i);
			return (NULL);
		}
		map = tmp_map;
		map[i] = line;
		i++;
		map_size = i;
	}
	if (!line && i == 0)
	{
		free_map(map, i);
		return (NULL);
	}
	map[i] = NULL;
	close(fd);
	return (map);
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

int	open_map_file(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\nopen", 10);
		return (-1);
	}
	return (fd);
}
int	check_for_ber(char *name)
{
	int	len;

	len = ft_strlen(name);
	if (len < 5 || name[0] == '.' || ft_strcmp(name + len - 4, ".ber") != 0)
	{
		write(2, "Error\n.ber", 10);
		return (0);
	}
	return (1);
}
int input(int key, t_game *game)
{
	if (key == ESC)
		exit(0);
	else if (key == 119)
	{
		if (move_up(game))
			printf("count = %d\n", game->count++);
	}
	else if (key == 115)
	{
		if (move_down(game))
			printf("count = %d\n", game->count++);
	}
	else if (key == 97)
	{
		if (move_left(game))
			printf("count = %d\n", game->count++);
	}
	else if (key == 100)
	{
		if (move_right(game))
			printf("count = %d\n", game->count++);	
	}
	return (0);
}
int	close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->win);
    exit(0);
}

int	change_places(t_game *game)
{
	int	i;
	int	j;
	i = game->player_y;
	j = game->player_x;
	if (game->o_map[i][j] == 'P')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->player, game->player_x * 64, game->player_y * 64);
		mlx_put_image_to_window(game->mlx, game->win, game->space, game->old_player_x * 64, game->old_player_y * 64);
		return (1);
	}
	return (0);
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
			if (game->o_map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->win, game->wall, j * 64, i * 64);
			else if (game->o_map[i][j] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, game->player, j * 64, i * 64);
			else if (game->o_map[i][j] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, game->collect, j * 64, i * 64);
			else if (game->o_map[i][j] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, game->exit, j * 64, i * 64);
			else
				mlx_put_image_to_window(game->mlx, game->win, game->space, j * 64, i * 64);
			j++;
		}
		i++;
	}
}
char **copy_map(char **map)
{
	int	i;
	int	j;
	char	**o_map;

	i = 0;
	j = 0;
	o_map = malloc(sizeof(char *) * 1);
	while (map[i])
	{
		o_map = ft_realloc(o_map, sizeof(char *) * i, sizeof(char *) * (i + 2));
		o_map[i] = ft_strdup(map[i]);
		i++;
	}
	o_map[i] = NULL;
	return (o_map);
}
int	main(int ac, char **av)
{
	int	i;
	int	fd;
	int	check_valid_map;
	i = 0;
	check_valid_map = 0;
	t_game 		game;
	game = (t_game){0};
	game.count = 1;
	if (ac != 2)
	{
		write(2, "Error\nacs", 9);
		return (0);
	}
	if (check_for_ber(av[1]) == 0)
		return (0);
	fd = open_map_file(av[1]);
	if (fd == -1)
	{
		write(2, "Error\nop", 8);
		return (0);
	}
	game.map = store_map(fd);
	game.o_map = copy_map(game.map);
	if (game.map == NULL)
	{
		write(2, "Error\nstore", 11);
		close(fd);
		return (0);
	}
	while (game.map[i])
	{
		if (validate_map_line(game.map[i]) == 0)
		{

			close(fd);
			free_map(game.map, game.rows);
			return (0);
		}
		i++;
	}
	if (all_walls(game.map) == 0)
	{
		close(fd);
		free_map(game.map, game.rows);
		write(2, "Error\nwalls", 11);
		return (0);
	}
	if (check_for_data(&game) == 0)
	{
		close(fd);
		free_map(game.map, game.rows);
		return (0);
	}
	game.rows = i;
	if (chack_valid_path(&game) == 0)
	{
		write(2, "Error\ncep", 10);
		close(fd);
		free_map(game.map, game.rows);
		return (0);
	}
	close(fd);
	game_in(&game);
	free_map(game.map, game.rows);
	return (1);
}
