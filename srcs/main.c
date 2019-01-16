/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:49:22 by wta               #+#    #+#             */
/*   Updated: 2019/01/16 07:43:30 by wta              ###   ########.fr       */
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
}

void	init_info(t_info *info)
{
	init_player(&info->player);
}

int		init_mlx(t_mlx *mlx)
{
	if (!(mlx->mlx_ptr = mlx_init()))
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "Wolf3D");
	if (!(mlx->win_ptr))
		return (0);
	if (!(mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H)))
		return (0);
	if (!(mlx->img_str = mlx_get_data_addr(mlx->img_ptr, &mlx->bpp
					, &mlx->sizel, &mlx->endian)))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_info	info;
	int		err_id;
	
	err_id = 1;
	init_info(&info);
	if (ac > 1)
	{
		set_vec2(1., 0., &info.player.dir);
		if ((err_id = read_file(av[1], &info)) == 1
		&& (err_id = check_bounds(&info.m_info)) == 1)
		{
			if (!(init_mlx(&info.mlx)))
				return (0);
			raycasting(&info);
			mlx_put_image_to_window(info.mlx.mlx_ptr, info.mlx.win_ptr, info.mlx.img_ptr, 0, 0);
			mlx_loop(info.mlx.mlx_ptr);
		}
	}
	if (err_id != 1)
		err_handler(err_id);
	return (0);
}
