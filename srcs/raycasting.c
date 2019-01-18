/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 03:57:58 by wta               #+#    #+#             */
/*   Updated: 2019/01/18 15:47:03 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "wolf3d.h"

static void	get_ray_dir(int x, t_vec2 *ray_dir, t_info *info)
{
	t_player	*player;
	double		proj_x;

	player = &info->player;
	proj_x = 2. * (double)x / (double)SCREEN_W - 1.;
	*ray_dir = (t_vec2){player->dir.x + player->cam_dir.x * proj_x,
						player->dir.y + player->cam_dir.y * proj_x};
}

static void	dda_helper(double *side_dst, double *delt, int *curr_pos, int *step)
{
	*side_dst += *delt;
	*curr_pos += *step;
}

double		dda(int *side, t_vec2 *ray_dir, t_info *info)
{
	t_int2		curr_pos;
	t_vec2		delta;
	t_int2		step;
	t_vec2		side_dist;

	delta = (t_vec2){fabs(1. / ray_dir->x), fabs(1. / ray_dir->y)};
	curr_pos = (t_int2){info->player.pos.x, info->player.pos.y};
	side_dist = (t_vec2){(ray_dir->x >= 0.) ? ((curr_pos.x - info->player.pos.x
	+ 1) * delta.x) : ((info->player.pos.x - curr_pos.x) * delta.x), (ray_dir->y
	>= 0.) ? ((curr_pos.y - info->player.pos.y + 1) * delta.y) :
	((info->player.pos.y - curr_pos.y) * delta.y)};
	step = (t_int2){(ray_dir->x >= 0.) ? 1 : -1, (ray_dir->y >= 0.) ? 1 : -1};
	while (info->m_info.map[curr_pos.y][curr_pos.x] == '0')
	{
		if (side_dist.x < side_dist.y && !(*side = 0))
			dda_helper(&side_dist.x, &delta.x, &curr_pos.x, &step.x);
		else if ((*side = 1))
			dda_helper(&side_dist.y, &delta.y, &curr_pos.y, &step.y);
	}
	return (!*side ?
		(curr_pos.x - info->player.pos.x + (1. - step.x) / 2.) / ray_dir->x :
		(curr_pos.y - info->player.pos.y + (1. - step.y) / 2.) / ray_dir->y);
}

void	draw_walls(int x, int end, int side, double dist, t_info *inf, t_vec2 ray_dir)
{
	unsigned int	tex_x;
	int				tex_y;
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
		tex_y = (((start * 512 - SCREEN_H * 256 + line_h * 256)) *
		tex->height) / (line_h * 512);
		inf->mlx.img.img_str[x + (start * inf->mlx.img.sizel / 4)] =
		tex->img_str[tex->width * tex_y + tex_x];
	}
}

void	draw_tex_floor(int sy, int side, int x, t_info *inf, double dist, t_vec2 ray_dir)
{
	t_vec2	wall_grnd;
	double	weigth;
	t_int2	floor_tex;
	t_img	*tex;
	t_vec2	curr_floor;

	tex = &inf->m_info.texs[0];
	wall_grnd = (t_vec2){inf->player.pos.x + ray_dir.x * dist,
						inf->player.pos.y + ray_dir.y * dist};
	wall_grnd = !side ? (t_vec2){floor(wall_grnd.x), wall_grnd.y} :
						(t_vec2){wall_grnd.x, floor(wall_grnd.y)};
	while (++sy < SCREEN_H)
	{
		weigth = (SCREEN_H / (2. * sy - SCREEN_H)) / dist;
		if (weigth > 1.)
			weigth = 1.;
		curr_floor = vec2_add(vec2_multf(wall_grnd, weigth),
							vec2_multf(inf->player.pos, (1. - weigth)));
		floor_tex = (t_int2){(int)(curr_floor.x * tex[0].width) % tex[0].width,
						(int)(curr_floor.y * tex[0].height) % tex[0].height};
		inf->mlx.img.img_str[x + (sy * inf->mlx.img.sizel / 4)] =
		tex[0].img_str[tex[0].width * floor_tex.y + floor_tex.x];
		inf->mlx.img.img_str[x + ((SCREEN_H - sy) * inf->mlx.img.sizel / 4)] =
		tex[1].img_str[tex[1].width * floor_tex.y + floor_tex.x];
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
	if ((end = SCREEN_H / 2 + line_h / 2) > SCREEN_H)
		end = SCREEN_H;
	draw_walls(x, end, side, dist, info, ray_dir);
	info->options & OPT_FLOOR ?
	draw_tex_floor(end - 1, side, x, info, dist, ray_dir) :
	draw_floor(end, x, info);
}

void	raycasting(t_info *info)
{
	t_vec2	ray_dir;
	double	dist;
	int		screen_x;
	int		side;

	screen_x = -1;
	info->player.cam_dir = vec2_normalize(
								rotate2d(info->player.dir, M_PI / 2.));
	while (++screen_x < SCREEN_W)
	{
		side = -1;
		get_ray_dir(screen_x, &ray_dir, info);
		dist = dda(&side, &ray_dir, info);
		draw_line(screen_x, side, dist, info, ray_dir);
	}
}
