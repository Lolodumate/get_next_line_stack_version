/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:37:08 by laroges           #+#    #+#             */
/*   Updated: 2023/08/04 19:23:56 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

typedef struct s_gnl
{
	int				len;
	int				ret;
	char			*buffer;
	struct s_gnl	*next;
}	t_gnl;

char	*get_next_line(int fd);
char	*ft_cut_stash(char *str_stash);
char	*ft_put_line(char *str_stash);
char	*ft_put_stash(char *str_stash, t_gnl *stash);
t_gnl	*ft_read_line(int fd, t_gnl *stash, char *str_stash);
char	*ft_strchr(char *s, char c);
char	*ft_strcpy(char *dest, char *src);
size_t	ft_strlen(char *str);
t_gnl	*insert_stack(t_gnl *element, char *buffer, size_t ret);
t_gnl	*clear_stack(t_gnl *stash);

#endif
