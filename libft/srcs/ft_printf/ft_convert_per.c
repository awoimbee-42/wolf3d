/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_per.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 05:26:30 by wta               #+#    #+#             */
/*   Updated: 2018/11/24 16:39:19 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_per(int c, t_lpf *node)
{
	char	*str;

	str = NULL;
	if (!(str = ft_strnew(1)))
		return (NULL);
	str[0] = (char)c;
	if (node->width > 1 && node->flag & MINUS)
	{
		if (!(str = ft_strjoinfree(str, ft_strspace(node->width - 1))))
			return (NULL);
	}
	else if (node->width > 1)
	{
		if (node->flag & ZERO)
		{
			if (!(str = ft_strjoinfree(ft_strzero(node->width - 1), str)))
				return (NULL);
		}
		else if (!(str = ft_strjoinfree(
		ft_strspace(node->width - 1), str)))
			return (NULL);
	}
	return (str);
}
