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

A part ça c'est programmé avec les pieds, la variable c n'est pas utilisée, et read peut aussi retourner -1 en cas d'erreur, ce qui provoquera une boucle.
 *
 *
 */

#include "get_next_line.h"

gnl	new_stack(void)
{
	return (NULL);
}

Bool	is_empty(gnl stash)
{
	if (stash == NULL)
		return (true);
	return (false);
}

gnl	insert_stack(gnl stash, char *buf)
{
	gnl	element;

	element = malloc(sizeof(*element));
	if (element == NULL)
		return (NULL);
	if (/*stash == NULL ||*/ buf == NULL)
	{
		free(element);
		return (NULL);
	}
	element->buffer = buf;
	element->next = stash;
	return (element);
}

void	clear_element(gnl element)
{
	if (is_empty(element))
		return;
	free(element);
}

void	print_line(char *line)
{
	if (line == NULL)
		return ;
	printf("%s", line);
	
}

char	*ft_putline(gnl stash, int len/*, char *buf*/)
{
	int		i;
	int		j;
	char	*line;
	gnl	tmp;

	i = len - BUFFER_SIZE;
	j = 0;
	line = malloc(sizeof(char) * len + 1);
	if (line == NULL)
		return (NULL);
//	tmp = new_stack();
	while (i >= 0)
	{
		j = 0;
		while (j < BUFFER_SIZE && stash->buffer[j])
		{
			line[i + j] = stash->buffer[j];
			if (stash->buffer[j] == '\n')
				break ;
			j++;
		}
		if (i == 0)
			break ;
		else if (i >= BUFFER_SIZE)
			i -= BUFFER_SIZE;
		else if (i < BUFFER_SIZE)
			i = 0;
		tmp = stash->next;
		clear_element(stash);
		stash = tmp;
		printf("Valeur de i dans ft_putline : %d\n", i);
//		buf = stash->buffer;
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*buf;
	char	*line;
	int	len;
	int	ret;
	gnl	stash = new_stack();

	len = 0;
	ret = 1;
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buf == NULL)
		return (NULL);
	while (!ft_strchr(buf, '\n') && ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
			return (NULL);
		stash = insert_stack(stash, buf);
		stash->buffer = buf;
//		printf("Valeur de buf dans get_next_line : %s\n", buf); 
		len += BUFFER_SIZE;
	}
//	printf("\nValeur de len dans get_next_line : %d\n", len);
	line = malloc(sizeof(char) * len + 1);
	if (line == NULL)
		return (NULL);
	line = ft_putline(stash, len/*, buf*/);
	print_line(line);
	return (line);


/*	gnl	*tmp;

	if (is_empty(stash) || fd < 0)
		return (NULL);
	if (!is_empty(stash->next))
		tmp = stash->next;
	stash->buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (stash->buffer == NULL)
		return (NULL);
	if (!ft_strchr(stash->buffer, '\n'))
	{
		stash->ret = read(fd, stash->buffer, BUFFER_SIZE);
		if (stash->ret == -1)
		{
			free(stash->buffer);
			return (NULL);
		}
	}	
*/
}
