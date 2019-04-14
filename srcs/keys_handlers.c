/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:10:33 by awoimbee          #+#    #+#             */
/*   Updated: 2019/04/14 03:59:24 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		set_key_mvt(int key, int *key_pressed)
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

int			key_pressed(int key, void *param)
{
	t_info	*info;

	info = (t_info*)param;
	if (key == ESC)
		exit(0);
	set_key_mvt(key, &info->key_pressed);
	if (key == NUM_ZERO || key == OPT_FLOOR
		|| (key == K_PLUS && info->fov < 3.)
		|| (key == K_MINUS && info->fov > 0.33))
	{
		if (key == OPT_FLOOR)
			info->key_pressed ^= 0x20;
		else if (key == NUM_ZERO)
			info->key_pressed ^= 0x10;
		else if (key == K_PLUS)
			info->fov += 0.1;
		else if (key == K_MINUS)
			info->fov -= 0.1;
		raycasting(info);
		mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr,
			info->mlx.img.img_ptr, 0, 0);
	}
	return (0);
}

int			key_released(int key, void *param)
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

int			close_win(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int			apply_key(void *param)
{
	t_info	*info;
	t_img	*mnmap;
	t_vec2	mvt;
	int		key;

	info = (t_info*)param;
	key = info->key_pressed;
	mnmap = &info->m_info.minimap;
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
			mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr,
				mnmap->img_ptr, mnmap->width * 3, 0);
		show_usage(info);
	}
	return (0);
}
