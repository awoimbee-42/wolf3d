/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 03:57:58 by wta               #+#    #+#             */
/*   Updated: 2019/01/17 14:04:40 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "wolf3d.h"

void	get_ray_dir(int x, t_vec2 *ray_dir, t_info *info)
{
	t_player	*player;
	double		proj_x;

	player = &info->player;
	proj_x = 2. * (double)x / (double)SCREEN_W - 1.;
	*ray_dir = (t_vec2){player->dir.x + player->cam_dir.x * proj_x,
						player->dir.y + player->cam_dir.y * proj_x};
}

double	dda(int *side, t_vec2 *ray_dir, t_info *info)
{
	t_vec2		curr_pos;
	t_vec2		delta;
	t_vec2		step;
	t_vec2		side_dist;
	double		dist;

	delta = (t_vec2){fabs(1. / ray_dir->x), fabs(1. / ray_dir->y)};
	curr_pos = (t_vec2){(int)info->player.pos.x, (int)info->player.pos.y};
	side_dist = (t_vec2){ (ray_dir->x >= 0.) ? ((curr_pos.x - info->player.pos.x
	+ 1) * delta.x) : ((info->player.pos.x - curr_pos.x) * delta.x), (ray_dir->y
	>= 0.) ? ((curr_pos.y - info->player.pos.y + 1) * delta.y) :
	((info->player.pos.y - curr_pos.y) * delta.y)};
	step = (t_vec2){(ray_dir->x >= 0.) ? 1 : -1, (ray_dir->y >= 0.) ? 1 : -1};
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
		if (info->m_info.map[(int)curr_pos.y][(int)curr_pos.x] > '0')
			break ;
	}
	if (*side == 0)
		dist = (curr_pos.x - info->player.pos.x + (1. - step.x) / 2.) / ray_dir->x;
	else
		dist = (curr_pos.y - info->player.pos.y + (1. - step.y) / 2.) / ray_dir->y;
	return (dist);
}

void	draw_line(int x, int side, double dist, t_info *info, t_vec2 ray_dir)
{
	int	start;
	int	end;
	int	idx;
	int line_h;

	line_h = (int)(SCREEN_H / dist);
	if ((start = SCREEN_H / 2 - line_h / 2) < 0)
		start = 0;
	if ((end = SCREEN_H / 2 + line_h / 2) >= SCREEN_H)
		end = SCREEN_H - 1;
	idx = -1;
	while (++idx < start)
		info->mlx.img_str[x + (idx * info->mlx.sizel / 4)] = 0xb2b2ff;
	// #### WALL ####

		//calculate value of wall_x
	// ray_dir = vec2_normalize(ray_dir);
	fprintf(stderr, "%f + %f * %f\n", info->player.pos.y, dist, ray_dir.y);
	double wall_x; //where exactly the wall was hit
	if (side == 0)
		wall_x = info->player.pos.y + dist * ray_dir.y;
	else
		wall_x = info->player.pos.x + dist * ray_dir.x;
	wall_x -= floor(wall_x);
	fprintf(stderr, "wall_x : %f\n", wall_x);

	//x coordinate on the texture
	int tex_x = (int)(wall_x * TEX_WIDTH);
	if(side == 0 && ray_dir.x > 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	if(side == 1 && ray_dir.y < 0)
		tex_x = TEX_WIDTH - tex_x - 1;
	// fprintf(stderr, "wall_x : %f\n", wall_x);

	while (idx < end)
	{

		int d = idx * 256 - SCREEN_H * 128 + line_h * 128;
        // TODO: avoid the division to speed this up
        int tex_y = ((d * TEX_HEIGHT) / line_h) / 256;
		// fprintf(stderr, "color = info->m_info.textures[0].img_str[%d * %d + %d]\n",
		// 				TEX_HEIGHT, tex_y, tex_x);
		info->mlx.img_str[x + (idx * info->mlx.sizel / 4)] = info->m_info.textures[0].img_str[TEX_HEIGHT * tex_y + tex_x];
		idx++;
	}

	// #### WALL ####
	idx = end - 1;
	while (++idx < SCREEN_H - 1)
		info->mlx.img_str[x + (idx * info->mlx.sizel / 4)] = 0xf4a460;
}

void	raycasting(t_info *info)
{
	t_vec2	ray_dir;
	double	dist;
	int		screen_x;
	int		side;

	screen_x = -1;
	info->player.cam_dir = vec2_normalize(rotate2d(info->player.dir, M_PI / 2.));
	while (++screen_x < SCREEN_W)
	{
		side = -1;
		get_ray_dir(screen_x, &ray_dir, info);
		dist = dda(&side, &ray_dir, info);
		draw_line(screen_x, side, dist, info, ray_dir);
	}
}
