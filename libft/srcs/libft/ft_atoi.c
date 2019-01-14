/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 17:38:39 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 05:56:45 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sign_value(long value)
{
	return ((value < 0) ? -1 : 1);
}

int			ft_atoi(const char *str)
{
	long		sign;
	long		res;

	if (str != NULL)
	{
		res = 0;
		while (*str == ' ' || *str == '\f' || *str == '\n' || *str == '\r'
				|| *str == '\t' || *str == '\v')
			str++;
		sign = (*str == '-') ? -1 : 1;
		str = (*str == '-' || *str == '+') ? str + 1 : str;
		while (*str >= '0' && *str <= '9')
			res = res * 10 + (int)(*str++ - '0');
		res *= sign;
		return ((sign == ft_sign_value(res)) ? res : 0);
	}
	return (-1);
}
