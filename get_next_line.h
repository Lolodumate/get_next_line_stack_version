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

typedef struct s_post_n
{
	char	*str;
} t_post_n;

typedef struct s_gnl
{
	char		*buffer;
	struct	s_gnl	*next;
} t_gnl, *p_gnl;

char				*get_next_line(int fd);
char				*ft_putline(p_gnl stash, int len, t_post_n *post_n);
char				*ft_read_line(int fd, p_gnl stash, t_post_n *post_n);
char				*ft_strchr(char *s, char c);
char				*ft_strcpy(char *dest, char *src);
p_gnl			insert_stack(p_gnl element, char *buffer);
int		ft_line_lenght(int fd);
t_post_n        *ft_post_n(t_post_n *post_n);
void	*ft_calloc(size_t nmemb, size_t size);
p_gnl	clear_stack(p_gnl element);

# endif
