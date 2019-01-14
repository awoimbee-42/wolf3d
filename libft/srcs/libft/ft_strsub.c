/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 12:06:19 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 06:01:55 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	new = NULL;
	if (s != NULL && (new = ft_strnew(len)) != NULL)
	{
		i = -1;
		while (++i < len)
			new[i] = s[start++];
	}
	return (new);
}
