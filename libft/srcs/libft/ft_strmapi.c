/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/05 22:11:26 by wta               #+#    #+#             */
/*   Updated: 2018/11/05 14:56:52 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	size_t			len;
	char			*new;

	new = NULL;
	if (s)
	{
		len = ft_strlen(s);
		if (!(new = (char*)malloc(sizeof(char) * (len + 1))))
			return (NULL);
		*(new + len) = 0;
		i = 0;
		while (s[i])
		{
			new[i] = (*f)(i, s[i]);
			i++;
		}
		return (new);
	}
	else
		return (NULL);
}
