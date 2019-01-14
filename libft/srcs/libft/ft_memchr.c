/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 02:57:20 by wta               #+#    #+#             */
/*   Updated: 2018/11/05 14:48:56 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*dst;

	dst = (const unsigned char*)s;
	while (n--)
		if (*dst++ == (unsigned char)c)
			return ((void*)dst - 1);
	return (NULL);
}
