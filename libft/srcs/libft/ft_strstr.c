/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 12:43:28 by wta               #+#    #+#             */
/*   Updated: 2018/08/09 03:08:10 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	len;

	if (!(*needle))
		return ((char*)haystack);
	len = ft_strlen(needle);
	while (*haystack)
		if ((ft_strncmp(haystack++, needle, len)) == 0)
			return ((char*)--haystack);
	return (NULL);
}
