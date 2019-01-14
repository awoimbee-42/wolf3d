/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 14:40:44 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 06:13:47 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*del_tab(char **tab, int len)
{
	int	i;

	if (tab)
	{
		i = -1;
		while (++i < len)
			ft_strdel(&tab[i]);
		free(tab);
		tab = NULL;
	}
	return (NULL);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**split;
	size_t	wdcount;
	int		i;

	split = NULL;
	if (s && c)
	{
		wdcount = ft_word_count(s, c);
		if ((split = (char**)malloc(sizeof(char*) * (wdcount + 1))) != NULL)
		{
			split[wdcount] = NULL;
			i = -1;
			while (*s != '\0')
			{
				if (*s != c)
				{
					if ((split[++i] = ft_wdcpy(s, c)) == NULL)
						return (del_tab(split, i));
				}
				s = (*s != c) ? s + ft_word_len(s, c) : s + 1;
			}
		}
	}
	return (split);
}
