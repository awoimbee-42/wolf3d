/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:48:50 by wta               #+#    #+#             */
/*   Updated: 2019/01/19 12:04:45 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define RD_ERR		2
# define BAD_FMT	3
# define MALLOC_ERR	4
# define GNL_ERR	5
# define READ_ERR	6
# define TOKENS		"@01"
# define WALL_S		2.
# define SHFT_32	0x100000000UL
# define SCREEN_W	1024
# define SCREEN_H	720
# define K_LEFT		123
# define K_UP		126
# define K_RIGHT	124
# define K_DOWN		125
# define NUM_ZERO	82
# define OPT_FLOOR	83
# define ESC		53

typedef struct	s_img
{
	void	*img_ptr;
	int		*img_str;
	int		width;
	int		height;
	int		bpp;
	int		sizel;
	int		endian;
}				t_img;

typedef struct	s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	void		*img_ptr;
	t_img		img;
}				t_mlx;

typedef struct	s_vec2
{
	double	x;
	double	y;
}				t_vec2;

typedef struct	s_int2
{
	int		x;
	int		y;
}				t_int2;

typedef struct	s_map
{
	t_img	minimap;
	char	**map;
	int		width;
	int		height;
	t_img	*texs;
}				t_map;

typedef struct	s_player
{
	t_vec2	pos;
	t_vec2	dir;
	t_vec2	cam_dir;
	int		fov;
}				t_player;

typedef struct	s_info
{
	int			options;
	t_player	player;
	t_map		m_info;
	t_mlx		mlx;
	int			key_pressed;
}				t_info;

typedef struct	s_delta
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int derror;
	int	error;
}				t_delta;

/*
**	vec2_op.c
*/
t_vec2	rotate2d(t_vec2 vector, const double theta);
t_vec2	vec2_add(t_vec2 a, const t_vec2 b);
t_vec2	vec2_sub(t_vec2 a, const t_vec2 b);
t_vec2	vec2_multv(t_vec2 a, const t_vec2 b);
t_vec2	vec2_multf(t_vec2 a, const double b);
t_vec2	vec2_div(t_vec2 a, const t_vec2 b);
t_vec2	vec2_divf(t_vec2 a, const double b);
double	vec2_dot(const t_vec2 a, const t_vec2 b);
double	vec2_mod(const t_vec2 a);
t_vec2	vec2_normalize(t_vec2 a);
double	points_dist(const t_vec2 p1, const t_vec2 p2);

void	raycasting(t_info *info);

int		read_file(char *file, t_info *info);
int		check_bounds(t_map *m_info);
t_img	*read_textures(void *mlx_ptr);

void	minimap(t_info *info);
void	pxl_to_img(t_img *img, int x, int y, int color);
void	fill_pixel(t_img *img, t_int2 a, t_int2 b, int color);

int		ft_strdelerr(char *line, int err_id);
int		splitdelerr(char **split, int err_id);
void	err_handler(int err_id);

int		splitlen(char **split);
void	splitdel(char **split);

#endif
