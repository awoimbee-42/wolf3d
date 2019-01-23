/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 16:04:39 by wta               #+#    #+#             */
/*   Updated: 2019/01/20 13:43:22 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "wolf3d.h"

void		init_info(t_info *info)
{
	info->player.pos = (t_vec2){-1., -1.};
	info->options = 0;
	info->key_pressed = 0;
	info->fov = 1.;
}

int			init_mlx(t_mlx *mlx)
{
	if (!(mlx->mlx_ptr = mlx_init()))
		return (0);
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, SCREEN_W, SCREEN_H, "Wolf3D");
	if (!(mlx->win_ptr))
		return (0);
	if (!(mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, SCREEN_W, SCREEN_H)))
		return (0);
	if (!(mlx->img.img_str = (int*)mlx_get_data_addr(mlx->img.img_ptr,
							&mlx->img.bpp, &mlx->img.sizel, &mlx->img.endian)))
		return (0);
	return (1);
}
