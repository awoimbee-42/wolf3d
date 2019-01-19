/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:49:22 by wta               #+#    #+#             */
/*   Updated: 2019/01/19 15:44:10 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "mlx.h"
#include "wolf3d.h"

void		init_player(t_player *player)
{
	player->pos = (t_vec2){-1., -1.};
	player->fov = 60;
}

void		init_info(t_info *info)
{
	init_player(&info->player);
	info->options = 0;
	info->key_pressed = 0;
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

static int	close_win(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

void		show_usage(t_info *info)
{
	mlx_string_put(info->mlx.mlx_ptr, info->mlx.win_ptr, 10, 0, 0xffffff,
			"Move           : Up/Down arrows");
	mlx_string_put(info->mlx.mlx_ptr, info->mlx.win_ptr, 10, 20, 0xffffff,
			"Strife         : A/D keys");
	mlx_string_put(info->mlx.mlx_ptr, info->mlx.win_ptr, 10, 40, 0xffffff,
			"Run            : Shift");
	mlx_string_put(info->mlx.mlx_ptr, info->mlx.win_ptr, 10, 60, 0xffffff,
			"Rotate         : Left/Right arrows");
	mlx_string_put(info->mlx.mlx_ptr, info->mlx.win_ptr, 10, 80, 0xffffff,
			"Minimap        : Numpad 0");
	mlx_string_put(info->mlx.mlx_ptr, info->mlx.win_ptr, 10, 100, 0xffffff,
			"Floor/Ceiling  : Numpad 1");
}

int			main(int ac, char **av)
{
	t_info	info;
	int		err_id;

	err_id = 1;
	init_info(&info);
	if (ac > 1)
	{
		info.player.dir = (t_vec2){1, 0};
		if ((err_id = read_file(av[1], &info)) == 1
				&& (err_id = check_bounds(&info.m_info)) == 1)
		{
			if (!(init_mlx(&info.mlx)))
				return (0);
			info.m_info.texs = read_textures(info.mlx.mlx_ptr);
			raycasting(&info);
			mlx_put_image_to_window(info.mlx.mlx_ptr, info.mlx.win_ptr,
									info.mlx.img.img_ptr, 0, 0);
			show_usage(&info);
			mlx_hook(info.mlx.win_ptr, 2, 0, key_pressed, &info);
			mlx_hook(info.mlx.win_ptr, 3, 0, key_released, &info);
			mlx_hook(info.mlx.win_ptr, 17, 0, close_win, NULL);
			mlx_loop_hook(info.mlx.mlx_ptr, apply_key, &info);
			mlx_loop(info.mlx.mlx_ptr);
		}
	}
	if (err_id != 1 || ac != 2)
		err_handler(err_id);
	return (0);
}
