/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 12:59:27 by wta               #+#    #+#             */
/*   Updated: 2019/01/18 15:03:05 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "wolf3d.h"

int		ft_round(float x)
{
	return ((int)(x + 0.5));
}

t_delta	init_delta(t_int2 a, t_int2 b)
{
	t_delta	delta;

	delta.dx = abs(ft_round(b.x) - ft_round(a.x));
	delta.dy = abs(ft_round(b.y) - ft_round(a.y));
	delta.sx = (a.x < b.x) ? 1 : -1;
	delta.sy = (a.y < b.y) ? 1 : -1;
	delta.derror = ((delta.dx > delta.dy) ? delta.dx : -(delta.dy)) / 2;
	delta.error = 0;
	return (delta);
}

int		is_out(t_int2 point, t_img *img)
{
	if (ft_round(point.x) < 0 || ft_round(point.x) > img->width - 1)
		return (1);
	if (ft_round(point.y) < 0 || ft_round(point.y) > img->height - 1)
		return (1);
	return (0);
}

void	fill_pixel(t_img *img, t_int2 a, t_int2 b, int color)
{
	t_delta	delta;

	delta = init_delta(a, b);
	while (1)
	{
		if (is_out(a, img) == 0 && is_out(b, img) == 0)
			img->img_str[ft_round(a.x) + ft_round(a.y) * img->sizel / 4] =
			color;
		if (a.x == b.x && a.y == b.y)
			break ;
		delta.error = delta.derror;
		if (delta.error > -(delta.dx))
		{
			delta.derror -= delta.dy;
			a.x += (double)delta.sx;
		}
		if (delta.error < delta.dy)
		{
			delta.derror += delta.dx;
			a.y += (double)delta.sy;
		}
	}
}

void	pxl_to_img(t_img *img, int x, int y, int color)
{
	img->img_str[x + (y * img->sizel / 4)] = color;
}
