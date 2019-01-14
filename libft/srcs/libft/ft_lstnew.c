/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 18:04:37 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 08:27:48 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*node;

	if ((node = (t_list*)malloc(sizeof(t_list))) != NULL)
	{
		if (content != NULL && (node->cnt = malloc(content_size)) != NULL)
		{
			ft_memcpy(node->cnt, content, content_size);
			node->content_size = content_size;
			node->next = NULL;
		}
		else
		{
			node->cnt = NULL;
			node->content_size = 0;
			node->next = NULL;
		}
	}
	return (node);
}
