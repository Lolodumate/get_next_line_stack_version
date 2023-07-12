/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laroges <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 17:37:36 by laroges           #+#    #+#             */
/*   Updated: 2023/06/23 17:37:39 by laroges          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*      Ressources :
 *      https://www.youtube.com/watch?v=-Mt2FdJjVno
 *      https://www.youtube.com/watch?v=vngK2abJ3_I&list=PLrWjmAwvhv61YP-7o56hnPINM80HsdJcw
 *      https://harm-smits.github.io/42docs/projects/get_next_line
 *      https://www.developpez.net/forums/d2120348/c-cpp/c/debuter/explication-methode-get-next-line/
 *      https://github.com/Yaten/42-get_next_line/blob/master/README.md
 *
 *      read(int fildes, void *buf, size_t nbytes)
 *
 *      libft interdite !!
 *
 *      Le programme doit compiler avec les options habituelle + -D BUFFER_SIZE=n
 *
 *      Une ligne se termine soit par un \n, soit par un EOF.
 *
 *      Ne pas copier le \n dans le paramètre d'entrée **line de la fonction
 *
 *      Valeurs retournées :
 *              1 si une ligne a été lue
 *              0 si la lecture a été correctement faite
 *              -1 si la lecture a échoué
 *
 *      Lorsqu'on atteint le EOF :
 *              On stocke le buffer dans **line. Si le buffer est vide, alors on stocke une string vide dans **line.
 *              On libère la mémoire allouée à l'exception du dernier bufferà stocker dans **line
 *
 *      Commentaire fonctionnement de read :
 *
 *      read : lit sur le "descripteur de fichier" 0 (c'est à dire l'entrée standard),et  place ce qui a été lu en mémoire à partir de l'adresse de buf, en se limitant à au plus 1 caractère. Ca tombe bien puisque buf, c'est une variable qui peut contenir qu'au plus 1 caractère.

si la lecture a réussi, écrit (write) ce caractère converti sur la sortie standard (1).
 *
 *
 */

#include "get_next_line.h"

p_gnl	insert_stack(p_gnl stash, char *buf)
{
	t_gnl	*element;

//	element = ft_calloc(1, sizeof(*element));
	element = malloc(sizeof(*element));
	if (element == NULL)
		return (NULL);
	if (buf == NULL)
	{
		free(element);
		return (NULL);
	}
	element->buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (element->buffer == NULL)
		return (NULL);
	ft_strcpy(element->buffer, buf);
	element->next = stash;
	return (element);
}

p_gnl	clear_stack(p_gnl stash)
{
	t_gnl	*element;

	if (stash == NULL)
		return (NULL);
	element = stash->next;
	free(stash->buffer);
	free(stash);
	return (element);
}
/*
void	print_line(char *line)
{
	if (line == NULL)
		return ;
	printf("%s", line);
	
}
*/
char	*ft_putline(p_gnl stash, int len, t_post_n *post_n)
{
	int		i;
	int		j;
	int		k;
	char	*line;

	i = len - BUFFER_SIZE;
	j = 0;
	k = 0;
	if (stash->buffer == NULL || len == 0/*stash->buffer[0] == '\0' || !stash->buffer[0]*/)
		return (NULL);
	line = ft_calloc(len + 1, sizeof(char));
//	line = malloc(sizeof(char) * len + 1);
	if (line == NULL)
		return (NULL);
	while (i >= 0)
	{
		j = 0;
		while (j < BUFFER_SIZE && stash->buffer[j])
		{
			line[i + j] = stash->buffer[j];
			if (stash->buffer[j] == '\n')
			{
				while (j < BUFFER_SIZE && stash->buffer[j])
				{
					post_n->str[k] = stash->buffer[j];
					j++;
					k++;
				}
				post_n->str[k] = '\0';
				break ;
			}
			j++;
		}
		if (i == 0)
			break ;
		else if (i >= BUFFER_SIZE)
			i -= BUFFER_SIZE;
		else if (i < BUFFER_SIZE)
			i = 0;
		stash = clear_stack(stash);
	}
	return (line);
}

char	*ft_read_line(int fd, p_gnl stash, t_post_n *post_n)
{
	char		*buf;
	static char		*line;
	unsigned int	len;
	int	ret;

	len = 0;
	ret = 1;
	buf = ft_calloc(BUFFER_SIZE + 1,  sizeof(char));
	if (buf == NULL)
		return (NULL);
	if (post_n->str != NULL && post_n->str[0] != '\0')
	{
		stash = insert_stack(stash, post_n->str);
		ft_strcpy(stash->buffer, post_n->str);
		free(post_n->str);
		free(post_n);
		len += BUFFER_SIZE;
	}
	while (!ft_strchr(buf, '\n') && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		stash = insert_stack(stash, buf);
		len += ret;
	}
	free(buf);
	line = ft_putline(stash, len, post_n);
//	print_line(line);
	return (line);
}

char	*get_next_line(int fd)
{
	p_gnl	stash;
	t_post_n	*post_n;
	static char	*line;

	stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	post_n = malloc(sizeof(*post_n));
	if (post_n == NULL)
		return (NULL);
	ft_post_n(post_n);
	line = ft_read_line(fd, stash, post_n);
	return (line);
}
