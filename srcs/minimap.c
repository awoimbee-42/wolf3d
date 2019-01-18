/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 09:30:25 by wta               #+#    #+#             */
/*   Updated: 2019/01/18 11:53:26 by wta              ###   ########.fr       */
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
	double	angle;

	angle = 0.;
	while (angle < M_PI * 2)
	{
		circle = (t_int2) {x + radius * cos(angle), y + radius * sin(angle)};
		minimap->img_str[circle.x + (circle.y * minimap->sizel / 4)] = 0xff0000;
		angle += 0.1;
	}
}

void	minimap(t_info *info)
{
	t_img	*mnmap;
	t_int2	map_pos;
	t_int2	real_pos;


	mnmap = &info->m_info.minimap;
	init_minimap(info);
	map_pos = (t_int2) {-1,-1};
	while (++map_pos.y < mnmap->height)
	{
		real_pos.y = map_pos.y * info->m_info.height / mnmap->height;
		map_pos.x = -1;
		while (++map_pos.x < mnmap->width)
		{
			real_pos.x = map_pos.x * info->m_info.width / mnmap->width;
			if (info->m_info.map[real_pos.y][real_pos.x] == '0')
				mnmap->img_str[map_pos.x + (map_pos.y * mnmap->sizel / 4)] = 0xf4a460;
			else
				mnmap->img_str[map_pos.x + (map_pos.y * mnmap->sizel / 4)] = 0x282828;
		}
	}
	draw_circle(info->player.pos.x * mnmap->width / info->m_info.width, info->player.pos.y * mnmap->height / info->m_info.height, 2., mnmap);
	mlx_put_image_to_window(info->mlx.mlx_ptr, info->mlx.win_ptr, mnmap->img_ptr,
			mnmap->width * 3, 0);
}
