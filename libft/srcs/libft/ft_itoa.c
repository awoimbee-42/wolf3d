/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 17:05:29 by wta               #+#    #+#             */
/*   Updated: 2018/08/09 17:55:53 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	size_t	len;
	long	nb;
	char	*str;

	len = ft_intlen_base(n, 10);
	if (!(str = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	*(str + len) = 0;
	nb = n;
	nb = (nb < 0) ? -nb : nb;
	while (len > 1)
	{
		len--;
		*(str + len) = nb % 10 + '0';
		nb /= 10;
	}
	*str = (n < 0) ? '-' : nb % 10 + '0';
	return (str);
}
