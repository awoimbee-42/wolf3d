/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 05:56:16 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 04:53:30 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa_pf(long long n, t_lpf *node)
{
	char		*str;
	long long	nb;
	int			len;

	str = NULL;
	len = ft_intlen_base(n, 10);
	len += (n >= 0) ? ((node->flag & PLUS) || (node->flag & SPACE)) : 0;
	if (!(str = ft_strnew(len)))
		return (NULL);
	nb = n;
	while (len > 1)
	{
		len--;
		str[len] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	if (nb >= 0 && node->flag & PLUS)
		str[0] = '+';
	else if (nb >= 0 && node->flag & SPACE)
		str[0] = ' ';
	else
		str[0] = (nb < 0) ? '-' : n % 10 + '0';
	return (str);
}

char	*ft_convert_acc(char *str, int len, t_lpf *node)
{
	if (ft_isdigit(str[0]) == 0)
	{
		if (!(str = ft_strinsert(
			str, ft_strzero(node->acc - len), !ft_isdigit(str[0]))))
			return (NULL);
	}
	else if (!(str = ft_strjoinfree(ft_strzero(node->acc - len), str)))
		return (NULL);
	return (str);
}

char	*ft_format(char *str, int len, t_lpf *node)
{
	if (node->flag & MINUS)
	{
		if (!(str = ft_strjoinfree(str, ft_strspace(node->width - len))))
			return (NULL);
	}
	else if (node->flag & ZERO && !(node->flag & SHARP)
		&& node->acc == 0 && *str != '\0')
	{
		if (!(str = ft_strinsert(
		str, ft_strzero(node->width - len), !ft_isdigit(str[0]))))
			return (NULL);
	}
	else if (!(str = ft_strjoinfree(ft_strspace(node->width - len), str)))
		return (NULL);
	return (str);
}

char	*ft_convert_d(long long n, t_lpf *node)
{
	char	*str;
	int		len;

	str = NULL;
	if (node->flag & CHAR)
		n = (char)n;
	else if (node->flag & SHORT)
		n = (short)n;
	if (n == 0 && (node->flag & ACC) && node->acc == 0)
		str = ft_strdup("");
	else if (!(str = ft_itoa_pf(n, node)))
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
