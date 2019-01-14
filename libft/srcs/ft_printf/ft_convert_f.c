/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_f.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 10:44:02 by wta               #+#    #+#             */
/*   Updated: 2018/11/25 19:35:16 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_intlen_f(long double n)
{
	long long	nbr;
	int			len;

	len = (n < 0) ? 1 : 0;
	nbr = n;
	if (nbr == 0)
		return (len + 1);
	while (nbr)
	{
		len++;
		nbr /= 10;
	}
	return (len);
}

char		*ft_itoa_f(long double n, t_lpf *node)
{
	long long	nb;
	char		*str;
	int			len;

	str = NULL;
	len = ft_intlen_f(n);
	len += (n >= 0) ? ((node->flag & PLUS) || (node->flag & SPACE)) : 0;
	if (!(str = ft_strnew(len)))
		return (NULL);
	nb = n;
	while (len > 1)
	{
		len--;
		str[len] = ft_abs(nb % 10) + '0';
		nb /= 10;
	}
	if (n >= 0 && node->flag & PLUS)
		str[0] = '+';
	else if (n >= 0 && node->flag & SPACE)
		str[0] = ' ';
	else
		str[0] = (n < 0) ? '-' : nb % 10 + '0';
	return (str);
}

char		*ft_dtoa(long double n, t_lpf *node)
{
	char		*res;
	char		*mant;
	char		point;
	int			i;

	res = NULL;
	if (!(res = ft_itoa_f(n, node)))
		return (NULL);
	if (!(node->flag & ACC))
		node->acc = 6;
	point = !((node->flag & ACC) && node->acc == 0);
	if (!(mant = ft_strnew(node->acc + point)))
		return (NULL);
	i = point - 1;
	mant[0] = (point) ? '.' : '0';
	if (node->acc > 0)
		n += (n * ft_pow(10, node->acc) >= .5)
			? (5 / ft_pow(10, node->acc + 1)) : 0;
	while (++i < node->acc + point)
	{
		n = ft_flush_double(n);
		mant[i] = ft_abs((int)n % 10) + '0';
	}
	res = ft_strjoinfree(res, mant);
	return (res);
}

char		*ft_convert_f(long double n, t_lpf *node)
{
	char	*str;
	int		len;

	if (n == 0 && (node->flag & ACC) && node->acc == 0)
		str = ft_strdup("");
	else if (!(str = ft_dtoa(n, node)))
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
