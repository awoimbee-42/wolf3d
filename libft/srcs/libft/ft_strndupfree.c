/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndupfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 23:34:50 by wta               #+#    #+#             */
/*   Updated: 2018/11/25 12:38:50 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndupfree(const char *s1, size_t len)
{
	char		*dest;
	size_t		i;

	if (!(dest = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (s1[++i] && i < len)
		dest[i] = s1[i];
	free((char*)s1);
	return (dest);
}
