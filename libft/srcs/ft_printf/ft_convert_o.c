/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_o.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 07:44:18 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 04:55:30 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_itoa_o(unsigned long long n, t_lpf *node)
{
	char	*str;
	int		len;

	str = NULL;
	len = ft_intlen_base_u(n, 8);
	len += (n != 0) ? (node->flag & SHARP) : 0;
	if (!(str = ft_strnew(len)))
		return (NULL);
	while (len > 1)
	{
		len--;
		str[len] = n % 8 + '0';
		n /= 8;
	}
	str[0] = ((node->flag & SHARP) && n != 0) ? '0' : n % 8 + '0';
	return (str);
}

char		*ft_convert_o(unsigned long long n, t_lpf *node)
{
	char	*str;
	int		len;

	if (node->flag & CHAR)
		n = (unsigned char)n;
	else if (node->flag & SHORT)
		n = (unsigned short)n;
	if (n == 0 && (node->flag & ACC) && node->acc == 0 && !(node->flag & SHARP))
		str = ft_strdup("");
	else if (!(str = ft_itoa_o(n, node)))
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
