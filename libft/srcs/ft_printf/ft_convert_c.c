/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_c.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 01:52:03 by wta               #+#    #+#             */
/*   Updated: 2018/11/24 16:37:03 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_c(int c, t_lpf *node)
{
	char	*str;

	str = NULL;
	if (!(str = ft_strnew(1)))
		return (NULL);
	if (c == 0)
		node->type = 0;
	str[0] = (char)c;
	if (node->width > 1 && node->flag & MINUS)
	{
		if (!(str = ft_strjoinfree(str, ft_strspace(node->width - 1))))
			return (NULL);
	}
	else if (node->width > 1
	&& !(str = ft_strjoinfree(ft_strspace(node->width - 1), str)))
		return (NULL);
	return (str);
}
