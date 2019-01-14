/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 02:35:47 by wta               #+#    #+#             */
/*   Updated: 2018/11/05 15:09:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*dest;
	unsigned char	*source;
	unsigned char	ref;

	ref = c;
	dest = (unsigned char*)dst;
	source = (unsigned char*)src;
	while (n--)
	{
		*dest++ = *source++;
		if (ref == *(source - 1))
			return (dest);
	}
	return (NULL);
}
