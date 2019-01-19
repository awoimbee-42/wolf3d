/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 09:30:25 by wta               #+#    #+#             */
/*   Updated: 2019/01/19 14:51:04 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "wolf3d.h"

#include <math.h>
#include <stdio.h>

void	init_minimap(t_info *info)
{
	t_img	*minimap;

	minimap = &info->m_info.minimap;
	minimap->width = SCREEN_W / 4;
	minimap->height = SCREEN_H / 4;
	minimap->img_ptr = mlx_new_image(info->mlx.mlx_ptr, minimap->width,
			minimap->height);
	minimap->img_str = (int*)mlx_get_data_addr(minimap->img_ptr, &minimap->bpp,
			&minimap->sizel, &minimap->endian);
}

void	draw_circle(double x, double y, double radius, t_img *minimap)
{
	t_int2	circle;
	t_int2	pos;
	double	angle;

	angle = 0.;
	pos = (t_int2){(int)x, (int)y};
	while (angle < M_PI * 2)
	{
		circle = (t_int2) {x + radius * cos(angle), y + radius * sin(angle)};
		fill_pixel(minimap, pos, circle, 0xff0000);
		angle += 0.1;
	}
}

void	draw_dir(t_player *player, t_img *minimap, t_map *m_info)
{
	t_int2	intpos;
	t_vec2	pos;
	t_int2	intdir;
	t_vec2	dir;

	pos = (t_vec2){player->pos.x * minimap->width / m_info->width,
		player->pos.y * minimap->height / m_info->height};
	dir = vec2_add(pos, vec2_multf(player->dir, 7.));
	intpos = (t_int2){(int)pos.x, (int)pos.y};
	intdir = (t_int2){(int)dir.x, (int)dir.y};
	fill_pixel(minimap, intpos, intdir, 0x0);
}

void	minimap(t_info *info)
{
	t_img	*mnmap;
	t_int2	map_pos;
	t_int2	real_pos;

	mnmap = &info->m_info.minimap;
	init_minimap(info);
	map_pos = (t_int2) {-1, -1};
	while (++map_pos.y < mnmap->height)
	{
		real_pos.y = map_pos.y * info->m_info.height / mnmap->height;
		map_pos.x = -1;
		while (++map_pos.x < mnmap->width)
		{
			real_pos.x = map_pos.x * info->m_info.width / mnmap->width;
			if (info->m_info.map[real_pos.y][real_pos.x] == '0')
				pxl_to_img(mnmap, map_pos.x, map_pos.y, 0xf4a460);
			else
				pxl_to_img(mnmap, map_pos.x, map_pos.y, 0x282828);
		}
	}
	draw_circle(info->player.pos.x * mnmap->width / info->m_info.width,
		info->player.pos.y * mnmap->height / info->m_info.height, 3., mnmap);
	draw_dir(&info->player, &info->m_info.minimap, &info->m_info);
	mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr,
		mnmap->img_ptr, mnmap->width * 3, 0);
}
