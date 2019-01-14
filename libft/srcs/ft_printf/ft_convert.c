/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 13:27:03 by wta               #+#    #+#             */
/*   Updated: 2018/11/25 14:18:36 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_typed(t_lpf *node, va_list ap)
{
	char	*str;

	str = NULL;
	if (node->flag & LLONG)
		if ((!(str = ft_convert_d(va_arg(ap, long long), node))))
			return (NULL);
	if (node->flag & LONG)
		if (!(str = ft_convert_d(va_arg(ap, long), node)))
			return (NULL);
	if (!(node->flag & LLONG) && !(node->flag & LONG))
		if (!(str = ft_convert_d(va_arg(ap, int), node)))
			return (NULL);
	return (str);
}

char	*ft_convert_typeu(t_lpf *node, va_list ap)
{
	char	*str;

	str = NULL;
	if (node->flag & LLONG)
		if ((!(str = ft_convert_u(va_arg(ap, unsigned long long), node))))
			return (NULL);
	if (node->flag & LONG)
		if (!(str = ft_convert_u(va_arg(ap, unsigned long), node)))
			return (NULL);
	if (!(node->flag & LLONG) && !(node->flag & LONG))
		if (!(str = ft_convert_u(va_arg(ap, unsigned int), node)))
			return (NULL);
	return (str);
}

char	*ft_convert_typeo(t_lpf *node, va_list ap)
{
	char	*str;

	str = NULL;
	if (node->flag & LLONG)
		if ((!(str = ft_convert_o(va_arg(ap, unsigned long long), node))))
			return (NULL);
	if (node->flag & LONG)
		if (!(str = ft_convert_o(va_arg(ap, unsigned long), node)))
			return (NULL);
	if (!(node->flag & LLONG) && !(node->flag & LONG))
		if (!(str = ft_convert_o(va_arg(ap, unsigned int), node)))
			return (NULL);
	return (str);
}

char	*ft_convert_typex(t_lpf *node, va_list ap)
{
	char	*str;

	str = NULL;
	if (node->flag & LLONG)
		if ((!(str = ft_convert_hex(va_arg(ap, unsigned long long), node))))
			return (NULL);
	if (node->flag & LONG)
		if (!(str = ft_convert_hex(va_arg(ap, unsigned long), node)))
			return (NULL);
	if (!(node->flag & LLONG) && !(node->flag & LONG))
		if (!(str = ft_convert_hex(va_arg(ap, unsigned int), node)))
			return (NULL);
	return (str);
}

char	*ft_convert_typef(t_lpf *node, va_list ap)
{
	char	*str;

	str = NULL;
	if (node->flag & LDOUBLE)
	{
		if ((!(str = ft_convert_f(va_arg(ap, long double), node))))
			return (NULL);
	}
	else if (!(str = ft_convert_f(va_arg(ap, double), node)))
		return (NULL);
	return (str);
}
