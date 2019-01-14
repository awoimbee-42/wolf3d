/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 15:00:18 by wta               #+#    #+#             */
/*   Updated: 2018/08/17 15:02:43 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstappend(t_list **alst, t_list *elem)
{
	t_list	*tmp;

	tmp = NULL;
	if (*alst && elem)
	{
		tmp = *alst;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
	else
	{
		*alst = elem;
	}
}
