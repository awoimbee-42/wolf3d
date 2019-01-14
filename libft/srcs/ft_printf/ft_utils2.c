/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 18:06:30 by wta               #+#    #+#             */
/*   Updated: 2018/11/25 18:09:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long double	ft_pow(long double n, int pow)
{
	long double	ret;

	if (pow == 0)
		return (1);
	ret = 1;
	while (pow)
	{
		ret *= n;
		pow--;
	}
	return (ret);
}

long double	ft_flush_double(long double n)
{
	long long	tmp;

	tmp = (long long)n;
	n -= (long double)tmp;
	n *= 10;
	return (n);
}
