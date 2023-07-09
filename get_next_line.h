/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:37:08 by laroges           #+#    #+#             */
/*   Updated: 2023/06/23 17:37:19 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef enum
{
	false,
	true
} Bool;

typedef struct gnl
{
	int			ret;
	char		*buffer;
	struct	gnl	*next;
} s_gnl, *gnl;

Bool					is_empty(gnl element);
char				*get_next_line(int fd);
char				*ft_putline(gnl stash, int len);
char				*ft_strchr(char *s, char c);
char				*ft_strcpy(char *dest, char *src);
gnl			next_stack(void);;
gnl			insert_stack(gnl element, char *buffer);
int		ft_line_lenght(int fd);
void	clear_element(gnl element);
void	*ft_calloc(size_t nmemb, size_t size);
void	clear_stack(gnl element);

# endif
