/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:49:22 by wta               #+#    #+#             */
/*   Updated: 2019/01/15 14:45:33 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "mlx.h"
#include "wolf3d.h"

void	init_vec2(t_vec2 *pos)
{
	pos->x = -1;
	pos->y = -1;
}

void	init_player(t_player *player)
{
	init_vec2(&player->pos);
	player->fov = 60;
	player->angle = 0;
}

void	init_info(t_info *info)
{
	init_player(&info->player);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		err_id;
	
	err_id = 1;
	init_info(&info);
	if (ac > 1)
	{
		if ((err_id = read_file(av[1], &info)) == 1
		&& (err_id = check_bounds(&info.m_info)) == 1)
		{
			
		}
	}
	if (err_id != 1)
		err_handler(err_id);
	return (0);
}
