/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 15:03:03 by wta               #+#    #+#             */
/*   Updated: 2018/08/01 15:06:15 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n-- && *s1++ == *s2++)
		if (*s1 == 0 && *s2 == 0)
			return (0);
	return (*(const unsigned char*)--s1 - *(const unsigned char*)--s2);
}
