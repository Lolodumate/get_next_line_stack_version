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
//	static char	*line;
	struct	gnl	*next;
} s_gnl, *gnl;

Bool				is_empty(gnl element);
char			*get_next_line(int fd);
char			*ft_putline(gnl stash, int len/*, char *buffer*/);
char			*ft_strchr(char *s, char c);
gnl		next_stack(void);;
gnl		insert_stack(gnl element, char *buffer);
void	clear_element(gnl element);
void	*ft_calloc(size_t nmemb, size_t size);
void	clear_stack(gnl element);


/*
char				*get_next_line(int fd);
char				*ft_strjoin(char *s1, char *s2);
char				*ft_putline(char *stash);
char				*ft_read_line(int fd, char *stash);
char				*ft_strchr(char *s, char c);
int			ft_get_n(char *line);
int			ft_count_line(char *line);
size_t		ft_strlen(char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	*ft_memset(void *s, int c, size_t n);
*/
# endif
