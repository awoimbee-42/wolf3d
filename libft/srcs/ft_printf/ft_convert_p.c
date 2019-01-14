/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_p.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 02:16:52 by wta               #+#    #+#             */
/*   Updated: 2018/11/25 11:18:28 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_plen(unsigned long ptr)
{
	int	len;

	len = (ptr == 0) ? 3 : 2;
	while (ptr)
	{
		len++;
		ptr /= 16;
	}
	return (len);
}

static char	*ft_ptoa(unsigned long ptr)
{
	char	*str;
	int		mod;
	int		len;

	str = NULL;
	len = ft_plen(ptr);
	if (!(str = ft_strnew(len)))
		return (NULL);
	str[0] = '0';
	str[1] = 'x';
	while (--len > 1)
	{
		mod = ptr % 16;
		str[len] = (mod > 9) ? 'a' + (mod % 10) : mod + '0';
		ptr /= 16;
	}
	return (str);
}

char		*ft_convert_p(unsigned long ptr, t_lpf *node)
{
	char	*str;
	int		len;

	str = NULL;
	if (!(str = ft_ptoa(ptr)))
		return (NULL);
	len = ft_strlen(str);
	if (node->width > len && node->flag & MINUS)
	{
		if (!(str = ft_strjoinfree(str, ft_strspace(node->width - len))))
			return (NULL);
	}
	else if (node->width > len)
		if (!(str = ft_strjoinfree(ft_strspace(node->width - len), str)))
			return (NULL);
	return (str);
}
