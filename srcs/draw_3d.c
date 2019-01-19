/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 13:17:37 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/19 15:07:26 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_walls(t_int2 col, double dist, int side, t_info *inf)
{
	unsigned int	tex_x;
	unsigned int	tex_y;
	t_img			*tex;
	int				start;
	int				line_h;

	line_h = (int)(SCREEN_H / dist);
	if ((start = SCREEN_H / 2 - line_h / 2 - 1) < -1)
		start = -1;
	tex_x = !side ? ((inf->player.pos.y + dist * inf->ray_dir.y) * SHFT_32) :
						((inf->player.pos.x + dist * inf->ray_dir.x) * SHFT_32);
	if (!side)
		tex = inf->ray_dir.x > 0 ? &inf->m_info.texs[0] : &inf->m_info.texs[1];
	else
		tex = inf->ray_dir.y < 0 ? &inf->m_info.texs[2] : &inf->m_info.texs[3];
	tex_x = (!side && inf->ray_dir.x > 0) || (side && inf->ray_dir.y < 0) ?
		tex->width - (double)tex_x * tex->width / SHFT_32 - 1 :
		(double)tex_x * tex->width / SHFT_32;
	while (++start < col.y)
	{
		tex_y = ((start * 2 - SCREEN_H + line_h) * tex->height) / (line_h * 2);
		inf->mlx.img.img_str[col.x + (start * inf->mlx.img.sizel / 4)] =
		tex->img_str[tex->width * tex_y + tex_x];
	}
}

/*
**	Take the pixel at the bottom of the wall and the player position
**		for each pixel between these 2, project a texture pixel
*/

void	draw_tex_floor(t_int2 col, double dist, t_info *inf)
{
	t_vec2	wall_grnd;
	double	ratio;
	t_int2	tex_coords[2];
	t_img	*tex;
	t_vec2	cur_pos;

	tex = &inf->m_info.texs[4];
	wall_grnd = (t_vec2){inf->player.pos.x + inf->ray_dir.x * dist,
						inf->player.pos.y + inf->ray_dir.y * dist};
	while (col.y < SCREEN_H)
	{
		ratio = (SCREEN_H / (2. * col.y - SCREEN_H)) / dist;
		ratio > 1. ? ratio = 1 : 0;
		cur_pos = vec2_add(vec2_multf(wall_grnd, ratio),
							vec2_multf(inf->player.pos, (1 - ratio)));
		tex_coords[0] = (t_int2){(int)(cur_pos.x * tex[0].width) % tex[0].width,
						(int)(cur_pos.y * tex[0].height) % tex[0].height};
		tex_coords[1] = (t_int2){(int)(cur_pos.x * tex[1].width) % tex[1].width,
						(int)(cur_pos.y * tex[1].height) % tex[1].height};
		pxl_to_img(&inf->mlx.img, col.x, col.y,
		tex[0].img_str[tex[0].width * tex_coords[0].y + tex_coords[0].x]);
		pxl_to_img(&inf->mlx.img, col.x, SCREEN_H - col.y,
		tex[1].img_str[tex[1].width * tex_coords[1].y + tex_coords[1].x]);
		++col.y;
	}
}

void	draw_floor(t_int2 col, t_info *inf)
{
	while (col.y < SCREEN_H)
	{
		inf->mlx.img.img_str[col.x + col.y * inf->mlx.img.sizel / 4] = 0xf4a460;
		inf->mlx.img.img_str
		[col.x + ((SCREEN_H - col.y - 1) * inf->mlx.img.sizel / 4)] = 0xb2b2ff;
		++col.y;
	}
}

void	draw_line(int x, int side, double dist, t_info *info)
{
	int		line_h;
	t_int2	floor_start;

	line_h = (int)(SCREEN_H / dist);
	floor_start.x = x;
	if ((floor_start.y = SCREEN_H / 2 + line_h / 2) > SCREEN_H
	|| floor_start.y < 0)
		floor_start.y = SCREEN_H;
	draw_walls(floor_start, dist, side, info);
	if (info->key_pressed & 0x20)
		draw_tex_floor(floor_start, dist, info);
	else
		draw_floor(floor_start, info);
}
