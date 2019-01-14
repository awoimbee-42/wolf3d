/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/17 14:42:11 by wta               #+#    #+#             */
/*   Updated: 2018/08/17 15:42:41 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new_lst;

	new_lst = NULL;
	if (lst && (*f))
	{
		while (lst)
		{
			ft_lstappend(&new_lst, (*f)(lst));
			lst = lst->next;
		}
	}
	else
		return (NULL);
	return (new_lst);
}
