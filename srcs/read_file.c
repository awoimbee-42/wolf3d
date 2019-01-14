/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:40:31 by wta               #+#    #+#             */
/*   Updated: 2019/01/14 13:17:53 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/includes/libft.h"
#include "wolf3d.h"

int		splitlen(char **split)
{
	int	i;

	i = 0;
	if (split != NULL)
	{
		while (split[i] != NULL)
			i++;
	}
	return (i);
}

int		parse_first_line(char *str)
{
	char	**split;
	int		len;

	if ((split = ft_strsplit(str, ' ')) != NULL && (len = splitlen(split) == 2))
	{

	}
}

int		read_file(char *file)
{
	char	*line;
	int		ret;
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (-1);
	if ((ret = get_next_line(fd, &line)) <= 0)
		return (RD_ERR);
	return (0);
}
