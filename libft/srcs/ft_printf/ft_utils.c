/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 01:15:37 by wta               #+#    #+#             */
/*   Updated: 2018/11/25 11:36:50 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_is_arg(char c)
{
	char	*buf;
	int		i;

	buf = "%cspdiouxXf";
	i = -1;
	while (buf[++i])
		if (buf[i] == c)
			return (1);
	return (0);
}

char	*ft_strspace(int len)
{
	char	*new;
	int		i;

	new = NULL;
	if (!(new = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = ' ';
	return (new);
}

char	*ft_strzero(int len)
{
	char	*new;
	int		i;

	new = NULL;
	if (!(new = ft_strnew(len)))
		return (NULL);
	i = -1;
	while (++i < len)
		new[i] = '0';
	return (new);
}

char	*ft_strinsert(char *s1, char *s2, int index)
{
	char	*output;
	int		i;
	int		j;

	output = NULL;
	if (!(output = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	i = -1;
	while (++i < index)
		output[i] = s1[i];
	j = -1;
	while (s2[++j])
		output[i + j] = s2[j];
	while (s1[i])
	{
		output[i + j] = s1[i];
		i++;
	}
	ft_strdel(&s1);
	ft_strdel(&s2);
	return (output);
}

int		ft_abs(long long n)
{
	return (n < 0 ? -n : n);
}
