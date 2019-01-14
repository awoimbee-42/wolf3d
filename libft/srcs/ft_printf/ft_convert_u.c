/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_u.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 06:06:10 by wta               #+#    #+#             */
/*   Updated: 2018/11/25 13:25:36 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_intlen_base_u(unsigned long long n, int base)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		len++;
		n /= base;
	}
	return (len);
}

static char	*ft_itoa_u(unsigned long long n)
{
	char	*str;
	int		len;

	str = NULL;
	len = ft_intlen_base_u(n, 10);
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len > 0)
	{
		len--;
		str[len] = n % 10 + '0';
		n /= 10;
	}
	return (str);
}

char		*ft_convert_u(unsigned long long n, t_lpf *node)
{
	char	*str;
	int		len;

	str = NULL;
	if (node->flag & CHAR)
		n = (unsigned char)n;
	else if (node->flag & SHORT)
		n = (unsigned short)n;
	if (n == 0 && (node->flag & ACC) && node->acc == 0)
		str = ft_strdup("");
	else if (!(str = ft_itoa_u(n)))
		return (NULL);
	len = ft_strlen(str);
	if (*str != '\0' && node->acc > len - (!ft_isdigit(str[0]))
	&& !(str = ft_convert_acc(str, len - !ft_isdigit(str[0]), node)))
		return (NULL);
	len = ft_strlen(str);
	if (node->width > len)
		str = ft_format(str, len, node);
	return (str);
}
