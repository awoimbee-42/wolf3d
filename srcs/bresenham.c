/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 12:59:27 by wta               #+#    #+#             */
/*   Updated: 2019/01/18 23:40:39 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf3d.h"

static void	draw_line_higrad(t_int2 p0, t_int2 p1, t_img *img, int color)
{
	t_int2	delta;
	int			way_x;
	int			error;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	way_x = 1;
	if (delta.x < 0 && (delta.x *= -1))
		way_x = -1;
	error = 2 * delta.x - delta.y;
	while (p0.y < p1.y)
	{
		pxl_to_img(img, p0.x, p0.y, color);
		if (error > 0)
		{
			p0.x += way_x;
			error -= 2 * delta.y;
		}
		error += 2 * delta.x;
		++p0.y;
	}
}

static void	draw_line_lograd(t_int2 p0, t_int2 p1, t_img *img, int color)
{
	t_int2	delta;
	int			way_y;
	int			error;

	delta.x = p1.x - p0.x;
	delta.y = p1.y - p0.y;
	way_y = 1;
	if (delta.y < 0 && (delta.y *= -1))
		way_y = -1;
	error = 2 * delta.y - delta.x;
	while (p0.x < p1.x)
	{
		pxl_to_img(img, p0.x, p0.y, color);
		if (error > 0)
		{
			p0.y += way_y;
			error -= 2 * delta.x;
		}
		error += 2 * delta.y;
		++p0.x;
	}
}

void		fill_pixel(t_img *img, t_int2 p0, t_int2 p1, int color)
{
	if (abs(p1.y - p0.y) < abs(p1.x - p0.x))
	{
		if (p0.x > p1.x)
			draw_line_lograd(p1, p0, img, color);
		else
			draw_line_lograd(p0, p1, img, color);
	}
	else
	{
		if (p0.y > p1.y)
			draw_line_higrad(p1, p0, img, color);
		else
			draw_line_higrad(p0, p1, img, color);
	}
}

void		pxl_to_img(t_img *img, int x, int y, int color)
{
	img->img_str[x + (y * img->sizel / 4)] = color;
}
