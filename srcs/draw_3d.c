/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 13:17:37 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/19 13:18:06 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	draw_walls(int x, int end, int side, double dist, t_info *inf, t_vec2 ray_dir)
{
	unsigned int	tex_x;
	unsigned int	tex_y;
	t_img			*tex;
	int				start;
	int				line_h;

	line_h = (int)(SCREEN_H / dist);
	if ((start = SCREEN_H / 2 - line_h / 2 - 1) < -1)
		start = -1;
	tex_x = !side ? ((inf->player.pos.y + dist * ray_dir.y) * SHFT_32) :
						((inf->player.pos.x + dist * ray_dir.x) * SHFT_32);
	if (!side)
		tex = (ray_dir.x > 0) ? &inf->m_info.texs[0] : &inf->m_info.texs[1];
	else
		tex = (ray_dir.y < 0) ? &inf->m_info.texs[2] : &inf->m_info.texs[3];
	tex_x = (!side && ray_dir.x > 0) || (side && ray_dir.y < 0) ?
		tex->width - (double)tex_x * tex->width / SHFT_32 - 1 :
		(double)tex_x * tex->width / SHFT_32;
	while (++start < end)
	{
		tex_y = ((start * 2 - SCREEN_H + line_h) * tex->height) / (line_h * 2);
		inf->mlx.img.img_str[x + (start * inf->mlx.img.sizel / 4)] =
		tex->img_str[tex->width * tex_y + tex_x];
	}
}

/*
**	Take the pixel at the bottom of the wall and the player position
**		for each pixel between these 2, project a texture pixel
*/

void	draw_tex_floor(int sy, int x, t_info *inf, double dist, t_vec2 ray_dir)
{
	t_vec2	wall_grnd;
	double	ratio;
	t_int2	tex_coords[2];
	t_img	*tex;
	t_vec2	curr_floor;

	tex = &inf->m_info.texs[4];
	wall_grnd = (t_vec2){inf->player.pos.x + ray_dir.x * dist,
						inf->player.pos.y + ray_dir.y * dist};
 	while (++sy < SCREEN_H)
	{
		ratio = (SCREEN_H / (2. * sy - SCREEN_H)) / dist;
		ratio > 1. ? ratio = 1 : 0;
		curr_floor = vec2_add(vec2_multf(wall_grnd, ratio),
							vec2_multf(inf->player.pos, (1 - ratio)));
		tex_coords[0] = (t_int2){(int)(curr_floor.x * tex[0].width) % tex[0].width,
						(int)(curr_floor.y * tex[0].height) % tex[0].height};
		tex_coords[1] = (t_int2){(int)(curr_floor.x * tex[1].width) % tex[1].width,
						(int)(curr_floor.y * tex[1].height) % tex[1].height};
		inf->mlx.img.img_str[x + (sy * inf->mlx.img.sizel / 4)] =
		tex[0].img_str[tex[0].width * tex_coords[0].y + tex_coords[0].x];
		inf->mlx.img.img_str[x + ((SCREEN_H - sy) * inf->mlx.img.sizel / 4)] =
		tex[1].img_str[tex[1].width * tex_coords[1].y + tex_coords[1].x];
	}
}

void	draw_floor(int start, int x, t_info *inf)
{
	while (start < SCREEN_H)
	{
		inf->mlx.img.img_str[x + (start * inf->mlx.img.sizel / 4)] = 0xf4a460;
		inf->mlx.img.img_str
		[x + ((SCREEN_H - start - 1) * inf->mlx.img.sizel / 4)] = 0xb2b2ff;
		++start;
	}
}

void	draw_line(int x, int side, double dist, t_info *info, t_vec2 ray_dir)
{
	int	end;
	int line_h;

	line_h = (int)(SCREEN_H / dist);
	if ((end = SCREEN_H / 2 + line_h / 2) > SCREEN_H || end < 0)
		end = SCREEN_H;
	draw_walls(x, end, side, dist, info, ray_dir);
	if (info->key_pressed & 0x20)
		draw_tex_floor(end - 1, x, info, dist, ray_dir);
	else
		draw_floor(end, x, info);
}