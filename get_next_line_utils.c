/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yaaitmou <yaaitmou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 20:45:32 by yaaitmou          #+#    #+#             */
/*   Updated: 2025/03/11 19:26:12 by yaaitmou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	if ((char)c == '\0')
		return ((char *)s + len);
	while (s[i])
	{
		if ((char)c == s[i])
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*string;
	size_t	i;
	size_t	lenmalloc;
	size_t	lenfors2;

	if ((s1 == NULL) || (s2 == NULL))
		return (NULL);
	i = 0;
	lenfors2 = 0;
	lenmalloc = ft_strlen(s1) + ft_strlen(s2);
	string = malloc(sizeof(char) * (lenmalloc + 1));
	if (!string)
		return (NULL);
	while (i < lenmalloc && s1[i] != '\0')
	{
		string[i] = s1[i];
		i++;
	}
	while (s2[lenfors2] != '\0' && i < lenmalloc)
		string[i++] = s2[lenfors2++];
	string[lenmalloc] = '\0';
	return (string);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*string;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	string = malloc(sizeof(char) * (len + 1));
	if (!string)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		string[i] = s[start + i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*dup;
	int		len;

	i = 0;
	len = ft_strlen(s1);
	dup = malloc(sizeof(char) * len + 1);
	if (!dup)
		return (NULL);
	while (s1[i])
	{
		dup[i] = s1[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
