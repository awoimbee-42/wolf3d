/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.41.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 03:57:58 by wta               #+#    #+#             */
/*   Updated: 2019/01/16 07:46:27 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <math.h>
#include "mlx.h"
#include "wolf3d.h"

void	get_ray_dir(int x, t_vec2 *ray_dir, t_info *info)
{
	t_player	*player;
	double		proj_x;

	player = &info->player;
	proj_x = 2. * (double)x / (double)SCREEN_W - 1.;
	set_vec2(player->dir.x + player->cam_dir.x * proj_x,
			player->dir.y + player->cam_dir.y * proj_x, ray_dir);	
}

double	dda(int *side, t_vec2 *ray_dir, t_info *info)
{
	t_vec2		curr_pos;
	t_vec2		delta;
	t_vec2		step;
	t_vec2		side_dist;
	double		dist;

	set_vec2(fabs(1. / ray_dir->x), fabs(1. / ray_dir->y),
			&delta);
	set_vec2(info->player.pos.x, info->player.pos.y, &curr_pos);
	set_vec2((ray_dir->x >= 0.) ? ((curr_pos.x - info->player.pos.x + 1) * delta.x)
			: ((info->player.pos.x - curr_pos.x) * delta.x), (ray_dir->y >= 0.)
			? ((curr_pos.y - info->player.pos.y + 1) * delta.y)
			: ((info->player.pos.y - curr_pos.y) * delta.y), &side_dist);
	set_vec2((ray_dir->x >= 0.) ? 1. : -1., (ray_dir->y >= 0.) ? 1. : -1., &step);
	while (1)
	{
		if (side_dist.x < side_dist.y)
		{
			side_dist.x += delta.x;
			curr_pos.x += step.x;
			*side = 0;
		}
		else
		{
			side_dist.y += delta.y;
			curr_pos.y += step.y;
			*side = 1;
		}
		if (info->m_info.map[(int)curr_pos.y][(int)curr_pos.x] > '0'
			&& info->m_info.map[(int)curr_pos.y][(int)curr_pos.x] != '@')
			break ;
	}
	if (*side == 0)
		dist = (curr_pos.x - info->player.pos.x + (1. - step.x) / 2.) / ray_dir->x;
	else
		dist = (curr_pos.y - info->player.pos.y + (1. - step.y) / 2.) / ray_dir->y;
	return (dist);
}

void	draw_line(int x, int side, int line_h, t_info *info)
{
	int	start;
	int	end;

	start = SCREEN_H / 2 - line_h / 2;
	start = (start < 0) ? 0 : start;
	end = SCREEN_H / 2 + line_h / 2;
	end = (end >= SCREEN_H) ? SCREEN_H - 1 : end;
	while (start < end)
	{
		*((unsigned int*)(info->mlx.img_str + x * info->mlx.bpp
					/ 8 + start * info->mlx.sizel)) = (side == 0) ? 0xFFFFFF : 0xd3d3d3;
		start++;
	}
}

void	raycasting(t_info *info)
{
	t_vec2	ray_dir;
	double	dist;
	int		screen_x;
	int		line_h;
	int		side;

	screen_x = -1;
	info->player.cam_dir = vec2_normalize(rotate2d(info->player.dir, M_PI / 2.));
	while (++screen_x < SCREEN_W)
	{
		side = -1;
		get_ray_dir(screen_x, &ray_dir, info);
		dist = dda(&side, &ray_dir, info);
		line_h = (int)(SCREEN_H / dist);
		draw_line(screen_x, side, line_h, info);
	}
}
