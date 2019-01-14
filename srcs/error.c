/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:37:02 by wta               #+#    #+#             */
/*   Updated: 2019/01/14 14:57:58 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include "../libft/includes/libft.h"
#include "wolf3d.h"

int		ft_strdelerr(char *line, int err_id)
{
	ft_strdel(&line);
	return (err_id);
}

int		splitdelerr(char **split, int err_id)
{
	splitdel(split);
	return (err_id);
}

void	err_handler(int err_id)
{
	char	buf[255];
	(void)err_id;
	ft_bzero(buf, 255);
	ft_strcpy(buf, "-Wolf3D: ");
	if (err_id == -1 || err_id == GNL_ERR)
		ft_strcat(buf, strerror(errno));
	if (err_id == RD_ERR)
		ft_strcat(buf, "Read error");
	if (err_id == BAD_FMT)
		ft_strcat(buf, "Bad format");
	if (err_id == MALLOC_ERR)
		ft_strcat(buf, "Allocation failed");
	ft_strcat(buf, "\n");
	ft_putstr_fd(buf, 2);
}