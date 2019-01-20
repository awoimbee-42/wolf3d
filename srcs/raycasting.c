/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 03:57:58 by wta               #+#    #+#             */
/*   Updated: 2019/01/20 14:17:35 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "wolf3d.h"

static void		get_ray_dir(int x, t_info *info)
{
	t_player	*player;
	double		proj_x;

	player = &info->player;
	proj_x = 2. * (double)x / (double)SCREEN_W - 1.;
	info->ray_dir = (t_vec2){player->dir.x + player->cam_dir.x * proj_x,
						player->dir.y + player->cam_dir.y * proj_x};
}

static void		dda_helper(double *side_dst, double *delt,
							int *curr_pos, int *step)
{
	*side_dst += *delt;
	*curr_pos += *step;
}

static double	dda(int *side, t_info *inf)
{
	t_int2		curr_pos;
	t_vec2		delt;
	t_int2		step;
	t_vec2		side_dist;

	delt = (t_vec2){fabs(1. / inf->ray_dir.x), fabs(1. / inf->ray_dir.y)};
	curr_pos = (t_int2){inf->player.pos.x, inf->player.pos.y};
	side_dist = (t_vec2){inf->ray_dir.x > 0 ? ((curr_pos.x - inf->player.pos.x
	+ 1) * delt.x) : (inf->player.pos.x - curr_pos.x) * delt.x, (inf->ray_dir.y
	>= 0.) ? ((curr_pos.y - inf->player.pos.y + 1) * delt.y) :
	((inf->player.pos.y - curr_pos.y) * delt.y)};
	step = (t_int2){inf->ray_dir.x > 0 ? 1 : -1, inf->ray_dir.y > 0 ? 1 : -1};
	while (inf->m_info.map[curr_pos.y][curr_pos.x] == '0')
	{
		if (side_dist.x < side_dist.y && !(*side = 0))
			dda_helper(&side_dist.x, &delt.x, &curr_pos.x, &step.x);
		else if ((*side = 1))
			dda_helper(&side_dist.y, &delt.y, &curr_pos.y, &step.y);
	}
	return (!*side ?
	(curr_pos.x - inf->player.pos.x + (1. - step.x) / 2.) / inf->ray_dir.x :
	(curr_pos.y - inf->player.pos.y + (1. - step.y) / 2.) / inf->ray_dir.y);
}

void			raycasting(t_info *info)
{
	int			screen_x;
	int			side;

	screen_x = -1;
	info->player.cam_dir = vec2_multf(rotate2d(info->player.dir, M_PI / 2.),
			info->fov);
	minimap(info);
	while (++screen_x < SCREEN_W)
	{
		side = -1;
		get_ray_dir(screen_x, info);
		info->dist = dda(&side, info);
		ray_minimap(&info->player, &info->ray_dir, &info->dist, &info->m_info);
		draw_line(screen_x, side, info->dist, info);
	}
}
