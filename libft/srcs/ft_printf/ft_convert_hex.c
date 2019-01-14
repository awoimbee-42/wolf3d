/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_hex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 08:11:30 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 04:53:18 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_hex(unsigned long long n, t_lpf *node)
{
	unsigned long long	nb;
	char				*str;
	int					caps;
	int					len;

	str = NULL;
	len = ft_intlen_base_u(n, 16) + ((n != 0 && (node->flag & SHARP)) ? 2 : 0);
	if (!(str = ft_strnew(len)))
		return (NULL);
	caps = (node->type == 'X') ? CAPS : 0;
	nb = n;
	while (len > (nb != 0 && (node->flag & SHARP) ? 2 : 0))
	{
		len--;
		str[len] = (n % 16 > 9) ? ((n % 16) % 10) + 'a' - caps : n % 16 + '0';
		n /= 16;
	}
	if (nb != 0 && node->flag & SHARP)
	{
		if (node->type == 'x')
			str = ft_strncpy(str, "0x", 2);
		else
			str = ft_strncpy(str, "0X", 2);
	}
	return (str);
}

char	*ft_convert_acc_hex(char *str, int len, t_lpf *node)
{
	if (str[1] == 'x' || str[1] == 'X')
	{
		if (!(str = ft_strinsert(
			str, ft_strzero(node->acc - len), 2)))
			return (NULL);
	}
	else if (!(str = ft_strjoinfree(ft_strzero(node->acc - len), str)))
		return (NULL);
	return (str);
}

char	*ft_format_hex(char *str, int len, t_lpf *node)
{
	if (node->flag & MINUS)
	{
		if (!(str = ft_strjoinfree(str, ft_strspace(node->width - len))))
			return (NULL);
	}
	else if (node->flag & ZERO && !(node->flag & ACC)
			&& node->acc == 0 && *str != '\0')
	{
		if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
		{
			if (!(str = ft_strinsert(
				str, ft_strzero(node->width - len), 2)))
				return (NULL);
		}
		else if (!(str = ft_strjoinfree(ft_strzero(node->width - len), str)))
			return (NULL);
	}
	else if (!(str = ft_strjoinfree(ft_strspace(node->width - len), str)))
		return (NULL);
	return (str);
}

char	*ft_convert_hex(unsigned long long n, t_lpf *node)
{
	char	*str;
	int		len;
	int		opt;

	if (node->flag & CHAR)
		n = (unsigned char)n;
	else if (node->flag & SHORT)
		n = (unsigned short)n;
	if (n == 0 && (node->flag & ACC) && node->acc == 0)
		str = ft_strdup("");
	else if (!(str = ft_itoa_hex(n, node)))
		return (NULL);
	len = ft_strlen(str);
	opt = (n != 0 && (node->flag & SHARP)) ? 2 : 0;
	if (*str != '\0' && node->acc > len - opt
	&& !(str = ft_convert_acc_hex(str, len - opt, node)))
		return (NULL);
	len = ft_strlen(str);
	if (node->width > len)
		str = ft_format_hex(str, len, node);
	return (str);
}
