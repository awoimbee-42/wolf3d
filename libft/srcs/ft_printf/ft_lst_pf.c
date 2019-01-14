/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 01:12:30 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 07:48:26 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_print_all(t_lpf *lpf, int *ret)
{
	t_lpf	*elem;

	if (lpf)
	{
		elem = lpf;
		while (elem)
		{
			if (elem->type == 0)
			{
				ft_putstr(elem->str);
				*ret += elem->ret + 1;
				write(1, "\0", 1);
			}
			else
			{
				ft_putstr(elem->str);
				*ret += elem->ret;
			}
			elem = elem->next;
		}
	}
}

t_lpf	*ft_pf_new(void)
{
	t_lpf	*new;

	new = NULL;
	if (!(new = (t_lpf*)malloc(sizeof(t_lpf))))
		return (NULL);
	new->next = NULL;
	new->flag = 0;
	new->width = 0;
	new->acc = 0;
	new->ret = 0;
	new->type = -1;
	new->str = NULL;
	return (new);
}

t_lpf	*ft_lpf_append(t_lpf **lpf, t_lpf *node)
{
	t_lpf	*elem;

	elem = NULL;
	if (*lpf != NULL)
	{
		elem = *lpf;
		while (elem->next)
			elem = elem->next;
		elem->next = node;
	}
	else
		*lpf = node;
	return (*lpf);
}

void	ft_rm_lst(t_lpf *lst)
{
	t_lpf	*elem;
	t_lpf	*tmp;

	elem = NULL;
	if (lst)
	{
		elem = lst;
		while (elem)
		{
			ft_strdel(&(elem->str));
			tmp = elem;
			elem = elem->next;
			free(tmp);
		}
	}
}

void	ft_error(t_lpf *lst)
{
	ft_rm_lst(lst);
	ft_putstr("error\n");
	exit(0);
}
