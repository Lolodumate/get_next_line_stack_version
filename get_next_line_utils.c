/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:38:08 by laroges           #+#    #+#             */
/*   Updated: 2023/06/23 17:38:10 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	size;

	size = 0;
	if (str == NULL)
		return (0);
	while (str[size])
		size++;
	return (size);
}

char	*ft_strchr(char *s, char c)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i])
	{
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	if (c == '\0')
		return (&s[i]);
	return (NULL);
}

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
/*
t_gnl	*ft_gnl(t_gnl *stash)
{
	stash->len = 0;
	stash->buffer = NULL;
	stash->next = NULL;
	return (stash);
}
*/

char	*ft_put_line(char *str_stash)
{
	int		i;
	char	*line;

	i = 0;
	if (str_stash == NULL)
		return (NULL);
	while (str_stash[i] && str_stash[i] != '\n')
		i++;
	if (!str_stash[i])
		return (NULL);
	i++;
	line = malloc(sizeof(char) * i + 1);
	if (line == NULL)
	{
		free(str_stash);
		return (NULL);
	}
	line[i + 1] = '\0';
	while (i-- >= 0)
		line[i] = str_stash[i];
	return (line);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	unsigned int		n;
	unsigned int		i;
	char	*ptr;

	n = nmemb * size;
	i = 0;
	ptr = NULL;
	if (nmemb != 0 && size != 0 && ((nmemb * size) / size) != nmemb)
		return (NULL);
	ptr = malloc(n);
	if (ptr == NULL)
		return (NULL);
	while (i < n)
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
