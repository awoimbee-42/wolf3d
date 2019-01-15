/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:48:50 by wta               #+#    #+#             */
/*   Updated: 2019/01/15 15:31:10 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define RD_ERR		2
# define BAD_FMT	3
# define MALLOC_ERR	4
# define GNL_ERR	5
# define READ_ERR	6
# define TOKENS		"01"
# define TEX_WIDTH	640
# define TEX_HEIGHT	640

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct	s_map
{
	char	**map;
	int		width;
	int		height;
	int		**textures;
}				t_map;

typedef struct	s_player
{
	t_vec2	pos;
	int		fov;
	int		angle;
}				t_player;

int		read_file(char *file, t_map *map_info);
int		**read_textures(mlx_ptr_t *mlx_ptr);

int		check_bounds(t_map *map_info);

int		ft_strdelerr(char *line, int err_id);
int		splitdelerr(char **split, int err_id);
void	err_handler(int err_id);

int		splitlen(char **split);
void	splitdel(char **split);

#endif
