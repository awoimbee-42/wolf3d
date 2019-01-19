/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 15:13:15 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/19 15:19:31 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

void		move(t_vec2 *pos, t_vec2 dir, char **map)
{
	if (map[(int)(pos->y + dir.y + 0.2)][(int)(pos->x + 0.2)] != '0'
		|| map[(int)(pos->y + dir.y + 0.2)][(int)(pos->x - 0.2)] != '0'
		|| map[(int)(pos->y + dir.y - 0.2)][(int)(pos->x + 0.2)] != '0'
		|| map[(int)(pos->y + dir.y - 0.2)][(int)(pos->x - 0.2)] != '0')
		dir.y = 0;
	if (map[(int)(pos->y + 0.2)][(int)(pos->x + dir.x + 0.2)] != '0'
		|| map[(int)(pos->y - 0.2)][(int)(pos->x + dir.x + 0.2)] != '0'
		|| map[(int)(pos->y + 0.2)][(int)(pos->x + dir.x - 0.2)] != '0'
		|| map[(int)(pos->y - 0.2)][(int)(pos->x + dir.x - 0.2)] != '0')
		dir.x = 0;
	*pos = vec2_add(*pos, dir);
}

t_vec2		set_mvt(int key, t_vec2 mvt, t_vec2 dir)
{
	double	div;

	div = (key & 0x100) ? 5. : 10.;
	if (key & 0x1)
		mvt = vec2_add(mvt, vec2_divf(dir, div));
	if (key & 0x2)
		mvt = vec2_sub(mvt, vec2_divf(dir, div));
	if (key & 0x40)
		mvt = vec2_add(mvt, rotate2d(vec2_divf(dir, div), -M_PI / 2));
	if (key & 0x80)
		mvt = vec2_add(mvt, rotate2d(vec2_divf(dir, div), M_PI / 2));
	return (mvt);
}

void		set_rot_mvt(int key, t_vec2 *dir)
{
	if (key & 0x4)
		*dir = rotate2d(*dir, -0.05);
	if (key & 0x8)
		*dir = rotate2d(*dir, 0.05);
}
