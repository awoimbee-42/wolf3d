/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:49:22 by wta               #+#    #+#             */
/*   Updated: 2019/01/17 13:50:08 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "mlx.h"
#include "wolf3d.h"

void	init_player(t_player *player)
{
	player->pos = (t_vec2){-1, -1};
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
	if (!(mlx->img_str = (int*)mlx_get_data_addr(mlx->img_ptr, &mlx->bpp
					, &mlx->sizel, &mlx->endian)))
		return (0);
	return (1);
}

void		move(t_vec2 *pos, t_vec2 dir, int forward, char **map)
{
	dir = vec2_divf(dir, 10.);
	if (!forward)
		dir = vec2_multf(dir, -1);
	if (map[(int)(pos->y + dir.y + 0.2)][(int)(pos->x + 0.2)] != '0'
	|| map[(int)(pos->y + dir.y + 0.2)][(int)(pos->x - 0.2)] != '0'
	|| map[(int)(pos->y + dir.y - 0.2)][(int)(pos->x + 0.2)] != '0'
	|| map[(int)(pos->y + dir.y - 0.2)][(int)(pos->x - 0.2)] != '0')
		dir.y = 0;
	if (map[(int)(pos->y + 0.2)][(int)(pos->x + dir.x + 0.2)] != '0'
	|| map[(int)(pos->y - 0.2)][(int)(pos->x + dir.x + 0.2)] != '0'
	|| map[(int)(pos->y + 0.2)][(int)(pos->x + dir.x - 0.2)] != '0'
	|| map[(int)(pos->y - 0.2)][(int)(pos->x + dir.x - 0.2)] != '0')
		dir.x = 0;
	*pos = vec2_add(*pos, dir);
}

int	key_move(int keycode, void *param)
{
	t_info	*info;

	info = (t_info*)param;
	if (keycode == 126 || keycode == 125 || keycode == 123 || keycode == 124)
	{
		if (keycode == KEY_LEFT)
			info->player.dir = rotate2d(info->player.dir, -0.05);
		if (keycode == KEY_UP)
			move(&info->player.pos, info->player.dir, 1, info->m_info.map);
		if (keycode == KEY_RIGHT)
			info->player.dir = rotate2d(info->player.dir, 0.05);
		if (keycode == KEY_DOWN)
			move(&info->player.pos, info->player.dir, 0, info->m_info.map);
		raycasting(info);
		mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr, info->mlx.img_ptr, 0, 0);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_info	info;
	t_img	*img;
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
			info.m_info.textures = read_textures(info.mlx.mlx_ptr);
			// mlx_put_image_to_window(info.mlx.mlx_ptr, info.mlx.win_ptr,
			// 						info.m_info.textures[1].img_ptr, 0, 0);
			raycasting(&info);
			mlx_put_image_to_window(info.mlx.mlx_ptr, info.mlx.win_ptr,
									img[1].img_ptr, 0, 0);
			mlx_hook(info.mlx.win_ptr, 2, 0, key_move, &info);
			mlx_loop(info.mlx.mlx_ptr);
		}
	}
	if (err_id != 1)
		err_handler(err_id);
	return (0);
}
