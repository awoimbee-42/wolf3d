/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/29 17:04:09 by wta               #+#    #+#             */
/*   Updated: 2018/11/06 07:28:57 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	i = 0;
	slen = ft_strlen(src);
	while (*dst && i++ < size)
		dst++;
	if (i - size - 1 == 0)
		return (--i + slen);
	dlen = i;
	while (*src && i++ < size - 1)
		*dst++ = *src++;
	*dst = 0;
	return (dlen + slen);
}
