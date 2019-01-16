/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_op0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:14:56 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/16 13:32:58 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

/*
**	theta is the angle by which we rotate the 2D vector around what we
**	could call (the axis) z.
*/

t_vec2		rotate2d(t_vec2 vector, const double theta)
{
	const double	cos_ = cos(theta);
	const double	sin_ = sin(theta);
	const double	tmp = vector.x;

	vector.x = vector.x * cos_ - vector.y * sin_;
	vector.y = vector.y * cos_ + tmp * sin_;
	return (vector);
}

/*
**	This is a whole 2d vector lib basically, we need to pick only what we need!
*/

t_vec2		vec2_add(t_vec2 a, const t_vec2 b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_vec2		vec2_sub(t_vec2 a, const t_vec2 b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_vec2		vec2_multv(t_vec2 a, const t_vec2 b)
{
	a.x *= b.x;
	a.y *= b.y;
	return (a);
}

t_vec2		vec2_multf(t_vec2 a, const double b)
{
	a.x *= b;
	a.y *= b;
	return (a);
}

t_vec2		vec2_div(t_vec2 a, const t_vec2 b)
{
	a.x /= b.x;
	a.y /= b.y;
	return (a);
}

t_vec2		vec2_divf(t_vec2 a, const double b)
{
	a.x /= b;
	a.y /= b;
	return (a);
}

double		vec2_dot(const t_vec2 a, const t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

double		vec2_mod(const t_vec2 a)
{
	return (sqrt(vec2_dot(a, a)));
}

t_vec2		vec2_normalize(t_vec2 a)
{
	double	length;

	length = vec2_mod(a);
	return (vec2_divf(a, length));
}

double		points_dist(const t_vec2 p1, const t_vec2 p2)
{
	return (sqrt(
		(p2.x - p1.x) * (p2.x - p1.x)
		+ (p2.y - p1.y) * (p2.y - p1.y)));
}
