/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 19:29:06 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/11 19:32:42 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_putnbr(int n)
{
	long int	nb;
	char		c;

	nb = n;
	if (n < 0)
	{
		write(1, "-", 1);
		n = -n;
	}
	if (n > 9)
		ft_putnbr(n / 10);
	c = nb % 10 + '0';
	write(1, &c, 1);
}

void	ft_printf(const char *format, ...)
{
	va_list	args;

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

int	close_window(t_game *game)
{
	ft_free_resources(game);
	exit(0);
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
