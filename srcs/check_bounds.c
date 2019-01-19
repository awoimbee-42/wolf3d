/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bounds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:33:57 by wta               #+#    #+#             */
/*   Updated: 2019/01/19 20:53:00 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int	check_bounds(t_map *map_info)
{
	int	idx;

	idx = -1;
	while (++idx < map_info->height)
	{
		if (map_info->map[idx][0] != '1'
		|| map_info->map[idx][map_info->width - 1] != '1')
			return (BAD_FMT);
	}
	idx = -1;
	while (++idx < map_info->width)
	{
		if (map_info->map[0][idx] != '1'
		|| map_info->map[map_info->height - 1][idx] != '1')
			return (BAD_FMT);
	}
	return (1);
}
