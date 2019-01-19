/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_op0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:14:56 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/19 13:44:00 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

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

t_vec2		vec2_multf(t_vec2 a, const double b)
{
	a.x *= b;
	a.y *= b;
	return (a);
}

t_vec2		vec2_divf(t_vec2 a, const double b)
{
	a.x /= b;
	a.y /= b;
	return (a);
}

t_vec2		vec2_normalize(t_vec2 a)
{
	double	length;

	length = sqrt(a.x * a.x + a.y * a.y);
	return (vec2_divf(a, length));
}
