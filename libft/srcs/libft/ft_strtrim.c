/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 16:53:56 by wta               #+#    #+#             */
/*   Updated: 2018/11/06 07:29:04 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_blank(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char			*ft_strtrim(char const *s)
{
	char	*new;
	size_t	len;

	new = NULL;
	if (s)
	{
		if (*s == 0)
			return ((char*)s);
		len = ft_strlen(s);
		while (len && ft_is_blank(*(s + len - 1)))
			len--;
		while (len && ft_is_blank(*s))
		{
			s++;
			len--;
		}
		if (!(new = ft_strnew(len)))
			return (NULL);
		new = (len) ? ft_strncpy(new, s, len) : new;
	}
	return (new);
}
