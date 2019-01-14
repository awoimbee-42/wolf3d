/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_pf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 01:14:56 by wta               #+#    #+#             */
/*   Updated: 2018/12/02 16:49:22 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_parse_mod(t_lpf *node, char *fmt)
{
	if (fmt[0] == 'h')
	{
		if (fmt[1] == 'h')
			node->flag |= CHAR;
		else if ((node->flag & CHAR) == 0)
			node->flag |= SHORT;
	}
	if (fmt[0] == 'l')
	{
		if (fmt[1] == 'l')
			node->flag |= LLONG;
		else if ((node->flag & LLONG) == 0)
			node->flag |= LONG;
	}
	if (fmt[0] == 'L')
		node->flag |= LDOUBLE;
	return (1);
}

void	ft_parse_opt(t_lpf *node, char *fmt, int *index, va_list ap)
{
	if (fmt[*index] == '*')
		node->width = va_arg(ap, int);
	if (fmt[*index] == '#')
		node->flag |= SHARP;
	if (fmt[*index] == '+')
		node->flag |= PLUS;
	if (fmt[*index] == '-')
		node->flag |= MINUS;
}

char	ft_parse_flag(t_lpf *node, char *fmt, int *index, va_list ap)
{
	*index -= 1;
	while (fmt[++(*index)] && ft_is_arg(fmt[*index]) == 0)
	{
		ft_parse_opt(node, fmt, index, ap);
		if (fmt[*index] == '.')
		{
			node->flag |= ACC;
			node->acc = ft_atoi(&fmt[*index + 1]);
		}
		if (fmt[*index] == '0' && node->width == 0)
			node->flag |= ZERO;
		if (ft_isdigit(fmt[*index]) && fmt[*index] != 0 && node->width == 0
				&& node->acc == 0)
			node->width = ft_atoi(&fmt[*index]);
		if (fmt[*index] == ' ')
			node->flag |= SPACE;
		ft_parse_mod(node, &fmt[*index]);
	}
	return ((ft_is_arg(fmt[*index])) ? fmt[*index] : 0);
}
