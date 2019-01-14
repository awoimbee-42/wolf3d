/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 19:18:54 by wta               #+#    #+#             */
/*   Updated: 2019/01/14 09:43:22 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*get_file(t_list **head, int fd)
{
	t_list	*elem;
	t_gnl	*gnl;

	elem = *head;
	gnl = NULL;
	while (elem)
	{
		if (((t_gnl*)elem->cnt)->fd == fd)
			return (elem);
		elem = elem->next;
	}
	if (!(elem = ft_lstnew(gnl, sizeof(t_gnl))))
		return (0);
	if (!(elem->cnt = (t_gnl*)malloc(sizeof(t_gnl))))
		return (0);
	gnl = elem->cnt;
	if (!(gnl->str = (char*)malloc(sizeof(char))))
		return (0);
	*(gnl->str) = '\0';
	gnl->fd = fd;
	ft_lstadd(head, elem);
	elem = *head;
	return (elem);
}

t_list			*rm_elem(t_list *list, int fd)
{
	t_list		*tmp;

	if (list == NULL)
		return (NULL);
	if (((t_gnl*)list->cnt)->fd == fd)
	{
		tmp = list->next;
		free(((t_gnl*)list->cnt)->str);
		free(list->cnt);
		free(list);
		tmp = rm_elem(tmp, fd);
		return (tmp);
	}
	else
	{
		list->next = rm_elem(list->next, fd);
		return (list);
	}
}

static char		*get_str(const int fd, char *cutover, int *ret)
{
	char	buf[BUFF_SIZE + 1];

	if (ft_strchr(cutover, '\n') != NULL)
		return (cutover);
	while ((*ret = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[*ret] = 0;
		if (!(cutover = ft_strjoindel(cutover, buf)))
			return (NULL);
		if (ft_strchr(buf, '\n'))
			return (cutover);
	}
	return (cutover);
}

char			*buf_trim(char **needle, char **str)
{
	char	*line;

	line = NULL;
	if ((*needle = ft_strchr(*str, '\n')))
	{
		**needle = 0;
		if (!(*needle = ft_strdup(*needle + 1)))
			return (0);
		if (!(line = ft_strdup(*str)))
			return (0);
		free(*str);
		*str = *needle;
	}
	else
	{
		if (!(line = ft_strdup(*str)))
			return (0);
		ft_strclr(*str);
	}
	return (line);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*lst_fd = NULL;
	t_list			*file;
	char			*needle;
	int				ret;

	file = NULL;
	needle = NULL;
	ret = 0;
	if (fd < 0 || line == NULL || read(fd, 0, 0) < 0)
	{
		lst_fd = rm_elem(lst_fd, fd);
		return (-1);
	}
	if ((file = get_file(&lst_fd, fd)) == NULL ||
	(((t_gnl*)file->cnt)->str = get_str(fd, ((t_gnl*)file->cnt)->str,
		&ret)) == NULL)
		return (-1);
	if (ret < BUFF_SIZE && (*(((t_gnl*)file->cnt)->str)) == '\0')
	{
		lst_fd = rm_elem(lst_fd, fd);
		return (0);
	}
	if (!(*line = buf_trim(&needle, &((t_gnl*)file->cnt)->str)))
		return (-1);
	return (1);
}
