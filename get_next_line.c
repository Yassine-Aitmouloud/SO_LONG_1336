/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 20:45:35 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/11 23:21:42 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_creat_left(char *left, char *buffer, int fd)
{
	int		check;
	char	*tmp;

	while (1)
	{
		check = read(fd, buffer, BUFFER_SIZE);
		if (check < 0)
			return (free(left), left = NULL, NULL);
		if (check == 0)
			break ;
		if (!left)
			left = ft_strdup("");
		if (!left)
			return (NULL);
		buffer[check] = '\0';
		tmp = left;
		left = ft_strjoin(tmp, buffer);
		if (!left)
			return (free(tmp), NULL);
		free(tmp);
		if (ft_strchr(left, '\n') != NULL)
			break ;
	}
	return (left);
}

char	*ft_line(char **line, char *left)
{
	int		i;
	char	*tmp;

	i = 0;
	while (left && left[i] != '\n' && left[i] != '\0')
		i++;
	if (left && left[i] == '\0')
	{
		if (left[0] == '\0')
			*line = NULL;
		else
			*line = ft_strdup(left);
		free(left);
		left = NULL;
	}
	else
	{
		*line = ft_substr(left, 0, i);
		tmp = left;
		left = ft_substr(tmp, i + 1, ft_strlen(tmp) - 1);
		free(tmp);
	}
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(left), NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	left = ft_creat_left(left, buffer, fd);
	free(buffer);
	if (!left)
		return (NULL);
	left = ft_line(&line, left);
	if (!line)
		return (free(left), left = NULL);
	return (line);
}
