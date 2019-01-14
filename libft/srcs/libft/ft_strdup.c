/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/28 21:02:40 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 04:25:57 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dest;
	size_t	size;
	size_t	i;

	size = ft_strlen(s1);
	if ((dest = ft_strnew(size)) != NULL)
	{
		i = -1;
		while (++i < size)
			dest[i] = s1[i];
	}
	return (dest);
}
