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

t_gnl	*insert_stack(t_gnl *stash, char *buf, size_t ret)
{
	t_gnl	*element;
	size_t	tmp;

	tmp = 0;
	element = malloc(sizeof(*element));
	if (element == NULL)
		return (NULL);
	element->buffer = ft_calloc(ret + 1, sizeof(char));
	if (element->buffer == NULL)
	{
		free(element);
		return (NULL);
	}
	ft_strcpy(element->buffer, buf);
	if (stash == NULL)
		tmp = 0;
	else
		tmp = stash->len;
	element->ret = ret;
	element->len = tmp + ret;
	element->next = stash;
	return (element);
}

t_gnl	*clear_stack(t_gnl *stash)
{
	t_gnl	*element;

	if (stash == NULL)
		return (NULL);
	element = stash->next;
	stash->len = 0;
	stash->ret = 0;
	free(stash->buffer);
	free(stash);
	return (element);
}

char	*ft_put_stash(char *str_stash, p_gnl stash)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = stash->len - stash->ret;
	str_stash[stash->len] = '\0';
	if (stash == NULL)
		return (NULL);
	while (stash != NULL)
	{
		while (j < stash->ret)
		{
			str_stash[i + j] = stash->buffer[j];
			j++;
		}
		stash = clear_stack(stash);
		if (stash != NULL)
			i -= stash->ret;
		j = 0;
	}
	return (str_stash);
}

p_gnl	ft_read_line(int fd, t_gnl *stash, char *str_stash)
{
	int		ret;
	char	*buf;

	ret = 1;
	if (fd < 0)
		return (NULL);
	if (str_stash != NULL && str_stash[0] != '\0')
		stash = insert_stack(stash, str_stash, ft_strlen(str_stash));
	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (buf == NULL)
		return (NULL);
	while (!ft_strchr(buf, '\n') && ret != 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if (ret == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[ret] = '\0';
		stash = insert_stack(stash, buf, ret);
	}
	free(buf);
	free(str_stash);
	if (!ft_strchr(stash->buffer, '\n'))
		stash = clear_stack(stash);
	return (stash);
}

char	*ft_cut_stash(char *str_stash)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (str_stash[i] && str_stash[i] != '\n')
		i++;
	if (!str_stash[i])
	{
		free(str_stash);
		return (NULL);
	}
	i++;
	tmp = ft_calloc(ft_strlen(str_stash) - i + 1, sizeof(char));
	if (tmp == NULL)
		return (NULL);
	while (str_stash[i])
		tmp[j++] = str_stash[i++];
	tmp[j] = '\0';
	free(str_stash);
	return (tmp);
}

char	*get_next_line(int fd)
{
	t_gnl	*stash;
	static char	*str_stash;
	char	*line;

	stash = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0/* || read(fd, &line, 0) < 0*/)
		return (NULL);
//	printf("DEBUT get_next_line - Valeur de str_stash : \n%s", str_stash);
	stash = ft_read_line(fd, stash, str_stash);
	if (stash == NULL)
		return (NULL);
	str_stash = ft_calloc(stash->len + 1, sizeof(char));
	if (str_stash == NULL)
		return (NULL);
	str_stash = ft_put_stash(str_stash, stash);
	if (str_stash == NULL)
	{
		printf("Erreur ! ft_put_stash = NULL !!\n");
	//	free(str_stash);
		return (NULL);
	}
//	printf("\n>>>>>>FIN 1 get_next_line - Valeur de str_stash : \n%s", str_stash);
//	printf("MARQUEUR - 1\n");
	line = ft_put_line(str_stash); 
//	printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>VALEUR DE LINE : %s", line);
	str_stash = ft_cut_stash(str_stash);
//	printf("\n>>>>>>FIN 2 get_next_line - Valeur de str_stash : \n%s", str_stash);
//	printf("MARQUEUR - 2\n");
//	printf("\n>>>>>>VALEUR DE LINE : %s", line);
	return (line);
}
