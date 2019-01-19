/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 03:57:58 by wta               #+#    #+#             */
/*   Updated: 2019/01/19 13:17:44 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "wolf3d.h"

static void		get_ray_dir(int x, t_vec2 *ray_dir, t_info *info)
{
	t_player	*player;
	double		proj_x;

	player = &info->player;
	proj_x = 2. * (double)x / (double)SCREEN_W - 1.;
	*ray_dir = (t_vec2){player->dir.x + player->cam_dir.x * proj_x,
						player->dir.y + player->cam_dir.y * proj_x};
}

static void		dda_helper(double *side_dst, double *delt, int *curr_pos, int *step)
{
	*side_dst += *delt;
	*curr_pos += *step;
}

static double	dda(int *side, t_vec2 *ray_dir, t_info *info)
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
