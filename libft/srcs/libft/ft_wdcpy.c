/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wdcpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:41:16 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 04:40:04 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_wdcpy(const char *s, char c)
{
	char	*dst;
	size_t	wdlen;
	size_t	i;

	dst = NULL;
	if (s != NULL)
	{
		wdlen = ft_word_len(s, c);
		if ((dst = ft_strnew(wdlen)) != NULL)
		{
			i = -1;
			while (++i < wdlen)
				dst[i] = s[i];
		}
	}
	return (dst);
}
