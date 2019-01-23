/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:49:22 by wta               #+#    #+#             */
/*   Updated: 2019/01/23 01:57:16 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	show_usage(t_info *info)
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
	mlx_string_put(info->mlx.mlx_ptr, info->mlx.win_ptr, 10, 120, 0xffffff,
			"FOV            : Numpad +/-");
}

void	mlx_flow(t_info *info)
{
	if (!(init_mlx(&info->mlx)))
		err_handler(MLX_ERR);
	info->m_info.texs = read_textures(info->mlx.mlx_ptr);
	raycasting(info);
	mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr,
							info->mlx.img.img_ptr, 0, 0);
	show_usage(info);
	mlx_hook(info->mlx.win_ptr, 2, 1L << 0, key_pressed, info);
	mlx_hook(info->mlx.win_ptr, 3, 1L << 1, key_released, info);
	mlx_hook(info->mlx.win_ptr, 17, 0, close_win, NULL);
	mlx_loop_hook(info->mlx.mlx_ptr, apply_key, info);
	mlx_loop(info->mlx.mlx_ptr);
}

int		main(int ac, char **av)
{
	t_info	info;
	int		err_id;

	err_id = 1;
	init_info(&info);
	if (ac == 2)
	{
		info.player.dir = (t_vec2){1, 0};
		if ((err_id = read_file(av[1], &info)) == 1
				&& (err_id = check_bounds(&info.m_info)) == 1)
				mlx_flow(&info);
	}
	if (err_id != 1 || ac != 2)
		err_handler(err_id);
	return (0);
}
