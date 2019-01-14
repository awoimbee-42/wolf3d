/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_s.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 01:16:45 by wta               #+#    #+#             */
/*   Updated: 2018/12/02 07:21:53 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_width_s(char *new, char *str, int len, t_lpf *node)
{
	if (node->width > len && node->flag & MINUS)
	{
		if (!(new = ft_strjoinfree(new, ft_strspace(node->width - len))))
			return (NULL);
	}
	else if (node->width > len)
	{
		if (!(new = ft_strjoinfree(ft_strspace(node->width - len), new)))
			return (NULL);
	}
	else if (!new && !(new = ft_strdup(str)))
		return (NULL);
	return (new);
}

char		*ft_convert_s(char *str, t_lpf *node)
{
	char	*new;
	int		len;

	new = NULL;
	if (str == NULL && !(new = ft_strdup("(null)")))
		return (NULL);
	if (!new && !(new = ft_strdup(str)))
		return (NULL);
	len = ft_strlen(new);
	if (((node->acc > 0 && node->acc < len) || (node->flag & ACC))
		&& !(new = ft_strndupfree(new, node->acc)))
		return (NULL);
	len = (new) ? ft_strlen(new) : len;
	if (!(new = ft_width_s(new, str, len, node)))
		return (NULL);
	return (new);
}
