/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:42:26 by wta               #+#    #+#             */
/*   Updated: 2018/11/05 14:53:37 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_word_count(char const *s, char c)
{
	size_t	count;
	int		word;

	count = 0;
	word = 0;
	if (s)
	{
		while (*s)
		{
			if (*s != c && !word)
			{
				word = 1;
				count++;
			}
			else if (*s == c && word)
				word = 0;
			s++;
		}
	}
	return (count);
}
