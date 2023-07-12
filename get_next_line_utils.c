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
/*
char	*ft_strjoin(char *s1, char *s2)
{
	char		*str;
	size_t	size_str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL)
	{
		s1 = ft_calloc(sizeof(char), 1);
		s1[0] = '\0';
	}
	size_str = ft_strlen(s1) + ft_strlen(s2);
	str = ft_calloc(sizeof(char), size_str + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s1);
	return (str);
}
*/
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

t_post_n	*ft_post_n(t_post_n *post_n)
{
	post_n->str = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
//	post_n->str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (post_n->str == NULL)
		return (NULL);
	return (post_n);
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
