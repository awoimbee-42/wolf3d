/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:37:55 by wta               #+#    #+#             */
/*   Updated: 2019/01/23 17:27:58 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	splitdel(char **split)
{
	int	i;

	if (split != NULL)
	{
		i = -1;
		while (split[++i] != NULL)
			ft_strdel(&split[i]);
		free(split);
		split = NULL;
	}
}
