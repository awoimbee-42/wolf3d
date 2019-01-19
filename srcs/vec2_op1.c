/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_op1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 13:44:12 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/19 13:44:44 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "wolf3d.h"

/*
**	theta is the angle by which we rotate the 2D vector around what we
**	could call (the axis) z.
*/

t_vec2		rotate2d(const t_vec2 vector, const double theta)
{
	const double	cos_ = cos(theta);
	const double	sin_ = sin(theta);

	return (
	(t_vec2)
	{
		vector.x * cos_ - vector.y * sin_,
		vector.y * cos_ + vector.x * sin_
	});
}