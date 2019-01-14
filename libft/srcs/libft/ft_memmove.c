/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 02:51:58 by wta               #+#    #+#             */
/*   Updated: 2018/11/05 15:05:51 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*source;
	unsigned char	*dest;

	if (dst == src)
		return (dst);
	dest = dst;
	source = (unsigned char*)src;
	if (src < dst)
		while (len--)
			*(dest + len) = *(source + len);
	else
		while (len--)
			*dest++ = *source++;
	return (dst);
}
