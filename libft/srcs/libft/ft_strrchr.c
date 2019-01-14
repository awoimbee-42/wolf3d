/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 12:19:30 by wta               #+#    #+#             */
/*   Updated: 2018/08/09 03:00:07 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		*tmp;
	char		ref;

	tmp = NULL;
	ref = c;
	while (*s)
		if (*s++ == ref)
			tmp = (char*)(s - 1);
	if (*s == ref)
		tmp = (char*)s;
	return (tmp);
}
