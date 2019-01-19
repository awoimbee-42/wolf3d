/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:49:22 by wta               #+#    #+#             */
/*   Updated: 2019/01/19 13:40:46 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
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
	info->options = 0;
	info->key_pressed = 0;
}

int		init_mlx(t_mlx *mlx)
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

void		move(t_vec2 *pos, t_vec2 dir, char **map)
{
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

void	set_key_mvt(int key, int *key_pressed)
{
	if (key == K_UP)
		*key_pressed |= 0x1;
	if (key == K_DOWN)
		*key_pressed |= 0x2;
	if (key == K_LEFT)
		*key_pressed |= 0x4;
	if (key == K_RIGHT)
		*key_pressed |= 0x8;
	if (key == K_A)
		*key_pressed |= 0x40;
	if (key == K_D)
		*key_pressed |= 0x80;
	if (key == K_SHIFT)
		*key_pressed |= 0x100;
}

#include <stdio.h>

int		key_pressed(int key, void *param)
{
	t_info	*info;

	info = (t_info*)param;
	if (key == ESC)
		exit(0);
	set_key_mvt(key, &info->key_pressed);
	if (key == NUM_ZERO || key == OPT_FLOOR)
	{
		info->key_pressed ^= (key == OPT_FLOOR) ? 0x20 : 0x10;
		raycasting(info);
		mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr,
			info->mlx.img.img_ptr, 0, 0);
	}

	return (0);
}

int		key_released(int key, void *param)
{
	t_info	*info;

	info = (t_info*)param;
	if (key == K_UP)
		info->key_pressed ^= 0x1;
	if (key == K_DOWN)
		info->key_pressed ^= 0x2;
	if (key == K_LEFT)
		info->key_pressed ^= 0x4;
	if (key == K_RIGHT)
		info->key_pressed ^= 0x8;
	if (key == K_A)
		info->key_pressed ^= 0x40;
	if (key == K_D)
		info->key_pressed ^= 0x80;
	if (key == K_SHIFT)
		info->key_pressed ^= 0x100;
	return (0);
}

t_vec2	set_mvt(int key, t_vec2 mvt, t_vec2 dir)
{
	double	div;

	div = (key & 0x100) ? 5. : 10.;
	if (key & 0x1)
		mvt = vec2_add(mvt, vec2_divf(dir, div));
	if (key & 0x2)
		mvt = vec2_sub(mvt, vec2_divf(dir, div));
	if (key & 0x40)
		mvt = vec2_add(mvt, rotate2d(vec2_divf(dir, div), -M_PI / 2));
	if (key & 0x80)
		mvt = vec2_add(mvt, rotate2d(vec2_divf(dir, div), M_PI / 2));
	return (mvt);
}

void	set_rot_mvt(int key, t_vec2 *dir)
{
	if (key & 0x4)
		*dir = rotate2d(*dir, -0.05);
	if (key & 0x8)
		*dir = rotate2d(*dir, 0.05);
}

int		apply_key(void *param)
{
	t_info	*info;
	t_vec2	mvt;
	int		key;

	info = (t_info*)param;
	key = info->key_pressed;
	if (key > 0)
	{
		mvt = (t_vec2){0., 0.};
		mvt = set_mvt(key, mvt, info->player.dir);
		move(&info->player.pos, mvt, info->m_info.map);
		set_rot_mvt(key, &info->player.dir);
		raycasting(info);
		mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr,
			info->mlx.img.img_ptr, 0, 0);
		if (key & 0x10)
			minimap(info);
	}
	return (0);
}

int		close_win(void)
{
	exit(0);
	return (0);
}

int		main(int ac, char **av)
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
			mlx_hook(info.mlx.win_ptr, 2, 0, key_pressed, &info);
			mlx_hook(info.mlx.win_ptr, 3, 0, key_released, &info);
			mlx_hook(info.mlx.win_ptr, 17, 0, close_win, NULL);
			mlx_loop_hook(info.mlx.mlx_ptr, apply_key, &info);
			mlx_loop(info.mlx.mlx_ptr);
		}
	}
	if (err_id != 1)
		err_handler(err_id);
	return (0);
}
