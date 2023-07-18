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

char	*ft_put_line(char *str_stash)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = 0;
	if (str_stash == NULL)
		return (NULL);
	while (str_stash[len] && str_stash[len] != '\n')
		len++;
/*	if (str_stash[len] == '\n')
		len++;
	else
		return (NULL);
*/	line = ft_calloc(len + 2, sizeof(char));
	if (line == NULL)
	{
		free(str_stash);
		return (NULL);
	}
	while (i < len)
	{
		line[i] = str_stash[i];
		i++;
	}
	if (str_stash[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
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
