/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 21:02:40 by wta               #+#    #+#             */
/*   Updated: 2018/11/23 00:01:43 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t len)
{
	char	*dest;
	size_t	i;

	if (!(dest = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (s1[++i] && i < len)
		dest[i] = s1[i];
	return (dest);
}
