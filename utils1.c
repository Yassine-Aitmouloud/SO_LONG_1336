#include "so_long.h"
int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1[i] == '\0' || s2[i] == '\0')
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	while (((unsigned char)s1[i] || (unsigned char)s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}
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
	map = NULL;
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
int	check_for_data(t_game *game)
{
	int	i;
	int	j;
	(*game).player_count = 0;
	(*game).collect_count = 0;
	(*game).exit_count = 0;
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
	if ((*game).player_count != 1 || (*game).exit_count != 1
		|| (*game).collect_count < 1)
	{
		write(2, "Err5r\n", 6);
		return (0);
	}
	return (1);
}
void	*ft_realloc(void *ptr, int old_size, int new_size)
{
	void	*new_ptr;
	int		copy_size;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	if (ptr)
	{
		if (old_size > 0)
		{
			if (old_size < new_size)
				copy_size = old_size;
			else
				copy_size = new_size;
			ft_memcpy(new_ptr, ptr, copy_size);
		}
		free(ptr);
	}
	return (new_ptr);
}
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	d = dst;
	s = src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
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
	int(i), (j) = {0};
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

int	chack_valid_path(t_game *map)
{
	int rows	= 0;
	int i, j, cols = 0;
	map->player_x = 0;
	map->player_y = 0;
	while (map->map[rows])
	{
		j = 0;
		while (map->map[rows][j])
		{
			j++;
		}
		rows++;
	}
	if (rows > 0)
		cols = ft_strlen(map->map[0]);
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'P')
			{
				map->player_x = j;
				map->player_y = i;
				break ;
			}
			j++;
		}
		i++;
	}
	
	flood_fill(map->map, map->player_y, map->player_x);
	i = 0;
	while (i < rows)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'E' || map->map[i][j] == 'C')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}
void	flood_fill(char **map, int y, int x)
{
	if (map[y][x] == 'E')
		map[y][x] = '1';
	if (y < 0 || x < 0 || !map[y] || !map[y][x] || map[y][x] == '1'
		|| map[y][x] == 'F')
		return ;
	map[y][x] = 'F';
	flood_fill(map, y + 1, x);
	flood_fill(map, y - 1, x);
	flood_fill(map, y, x + 1);
	flood_fill(map, y, x - 1);
}

void	ft_putnbr(int n)
{
	long int nb = n;
    if (n < 0)
    {
        write(1, "-", 1);
        n = -n;
    }
    if (n > 9)
        ft_putnbr(n / 10);
    char c = nb % 10 + '0';
    write(1, &c, 1);
}

void	ft_printf(const char *format, ...)
{
    va_list args;
    va_start(args, format);

    while (*format)
    {
        if (*format == '%' && (*(format + 1) == 'd' || *(format + 1) == 's'))
        {
            format++;
            if (*format == 'd')
                ft_putnbr(va_arg(args, int));
        }
        else
            write(1, format, 1);
        format++;
    }

    va_end(args);
}
void ft_free_image(t_game *game)
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
void ft_free_resources(t_game *game)
{
    if (!game)
        return;

    if (game->map)
    {
        free_map(game->map, game->rows);
        game->map = NULL;
    }
	if (game->o_map)
	{
		free_map(game->o_map, game->rows);
		game->o_map = NULL;
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

int close_window(t_game *game)
{
    ft_free_resources(game);
    exit(0);
}