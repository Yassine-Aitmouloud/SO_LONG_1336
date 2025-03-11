#include "so_long.h"

void	create_img(t_game *game)
{
	game->wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", &game->w, &game->h);
	if (!game->wall)
	{
		ft_free_resources(game);
		write(2, "Error\nwall", 10);
		exit(0);
	}
	game->player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", &game->w, &game->h);
	if (!game->player)
	{
		ft_free_resources(game);
		write(2, "Error\nplayer", 12);
		exit(0);
	}
	game->collect = mlx_xpm_file_to_image(game->mlx, "textures/coin.xpm", &game->w, &game->h);
	if (!game->collect)
	{
		ft_free_resources(game);
		write(2, "Error\ncollect", 13);
		exit(0);
	}
	game->exit = mlx_xpm_file_to_image(game->mlx, "textures/exit.xpm", &game->w, &game->h);
	if (!game->exit)
	{
		ft_free_resources(game);
		write(2, "Error\nexit", 11);
		exit(0);
	}
	game->space = mlx_xpm_file_to_image(game->mlx, "textures/space.xpm", &game->w, &game->h);
	if (!game->space)
	{
		ft_free_resources(game);
		write(2, "Error\nspace", 12);
		exit(0);
	}
}

size_t count_lines(const char *filename)
{
    size_t count = 0;
    char *line;
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        write(2, "Error\nopen\n", 11);
        return 0;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        count++;
        free(line);
    }
    close(fd);
    return count;
}

char **store_map(char *filename)
{
    size_t i = 0;
    size_t j = 0;
    char *line;
    char **map;
    size_t map_size;
    int fd = open(filename, O_RDONLY);

    if (fd == -1)
    {
        write(2, "Error\nopen\n", 11);
        return NULL;
    }
    map_size = count_lines(filename);
    if (map_size == 0)
    {
        write(2, "Error\nempty file\n", 17);
        close(fd);
        return NULL;
    }
    map = (char **)malloc(sizeof(char *) * (map_size + 1));
    if (!map)
    {
        write(2, "Error\nmalloc\n", 13);
        close(fd);
        return NULL;
    }
    while ((line = get_next_line(fd)) != NULL)
    {
        if (j == 0)
            j = ft_strlen(line);
        else if (ft_strlen(line) != j)
        {
            write(2, "Error\ninvalid line length\n", 26);
            free(line);
			line = get_next_line(-1); 
            free(line);
			free_map(map, i);
            close(fd);
            return NULL;
        }
        map[i] = line;
        i++;
    }
    map[i] = NULL;
    close(fd);
    return map;
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
char **copy_map(char **map, char *av)
{
	int	i;
	int	map_size;
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
int	main(int ac, char **av)
{
	int	i;
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
	game.map = store_map(av[1]);
	if (game.map == NULL)
	{
		ft_free_resources(&game);
		write(2, "Error\nstore", 11);
		return (0);
	}
	game.o_map = copy_map(game.map,av[1]);
	while (game.map[i])
	{
		if (validate_map_line(game.map[i]) == 0)
		{
			ft_free(game.map);
			ft_free(game.o_map);
			return (0);
		}
		i++;
	}
	if (all_walls(game.map) == 0)
	{
		ft_free(game.map);
		ft_free(game.o_map);
		write(2, "Error\nwalls", 11);
		return (0);
	}
	if (check_for_data(&game) == 0)
	{
		ft_free(game.map);
		ft_free(game.o_map);
		return (0);
	}
	game.rows = i;
	if (chack_valid_path(&game) == 0)
	{
		write(2, "Error\ncep", 10);
		ft_free_resources(&game);
		return (0);
	}
	if (!game_in(&game))
	{
		ft_free_resources(&game);
		return (0);
	}
	ft_free_resources(&game);
	return (1);
}
