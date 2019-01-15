/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate2d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 16:14:56 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/15 16:21:43 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
