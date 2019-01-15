/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:48:50 by wta               #+#    #+#             */
/*   Updated: 2019/01/15 16:33:30 by wta              ###   ########.fr       */
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
# define WALL_S		1
# define TEX_WIDTH	640
# define TEX_HEIGHT	640

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	char		*img_str;
	int			bpp;
	int			sizel;
	int			endian;
}				t_mlx;

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
	t_vec2	dir;
	int		fov;
}				t_player;

typedef struct	s_info
{
	t_player	player;
	t_map		m_info;
	t_mlx		mlx;
}				t_info;

int		read_file(char *file, t_info *info);
int		**read_textures(mlx_ptr_t *mlx_ptr);

int		check_bounds(t_map *m_info);

int		ft_strdelerr(char *line, int err_id);
int		splitdelerr(char **split, int err_id);
void	err_handler(int err_id);

int		splitlen(char **split);
void	splitdel(char **split);

#endif
