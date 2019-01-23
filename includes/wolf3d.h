/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 09:48:50 by wta               #+#    #+#             */
/*   Updated: 2019/01/23 01:57:38 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# define RD_ERR		2
# define BAD_FMT	3
# define MALLOC_ERR	4
# define GNL_ERR	5
# define READ_ERR	6
# define MLX_ERR	7
# define TOKENS		"@01"
# define SHFT_32	0x100000000UL
# define SCREEN_W	1200
# define SCREEN_H	720

# ifdef __linux__
#  define K_PLUS	61
#  define K_MINUS	45
#  define K_LEFT	65361
#  define K_UP		65362
#  define K_RIGHT	65363
#  define K_DOWN	65364
#  define K_A		97
#  define K_D		100
#  define K_SHIFT	257
#  define NUM_ZERO	48
#  define OPT_FLOOR	49
#  define ESC		65307
# else
#  define K_PLUS	000
#  define K_MINUS	000
#  define K_LEFT	123
#  define K_UP		126
#  define K_RIGHT	124
#  define K_DOWN	125
#  define K_A		0
#  define K_D		2
#  define K_SHIFT	257
#  define NUM_ZERO	82
#  define OPT_FLOOR	83
#  define ESC		53
# endif

# include "mlx.h"
# include <stdio.h> // printf in keyhandlers
# include <stdlib.h>
# include <stdlib.h>
# include <math.h>

typedef struct	s_img
{
	void		*img_ptr;
	int			*img_str;
	int			width;
	int			height;
	int			bpp;
	int			sizel;
	int			endian;
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
	double		x;
	double		y;
}				t_vec2;

typedef struct	s_int2
{
	int			x;
	int			y;
}				t_int2;

typedef struct	s_map
{
	t_img		minimap;
	char		**map;
	int			width;
	int			height;
	t_img		*texs;
}				t_map;

typedef struct	s_player
{
	t_vec2		pos;
	t_vec2		dir;
	t_vec2		cam_dir;
	int			fov;
}				t_player;

typedef struct	s_info
{
	int			options;
	t_player	player;
	t_map		m_info;
	t_mlx		mlx;
	int			key_pressed;
	double		fov;
	t_vec2		ray_dir;
	double		dist;
}				t_info;

void			init_info(t_info *info);
int				init_mlx(t_mlx *mlx);

/*
**	vec2_opX.c
*/
t_vec2			rotate2d(const t_vec2 vector, const double theta);
t_vec2			vec2_add(t_vec2 a, const t_vec2 b);
t_vec2			vec2_sub(t_vec2 a, const t_vec2 b);
t_vec2			vec2_multf(t_vec2 a, const double b);
t_vec2			vec2_divf(t_vec2 a, const double b);
t_vec2			vec2_normalize(t_vec2 a);

/*
**	keys_handlers.c
*/
void			set_key_mvt(int key, int *key_pressed);
int				key_pressed(int key, void *param);
int				key_released(int key, void *param);
int				apply_key(void *param);

/*
**	movements.c
*/
void			move(t_vec2 *pos, t_vec2 dir, char **map);
t_vec2			set_mvt(int key, t_vec2 mvt, t_vec2 dir);
void			set_rot_mvt(int key, t_vec2 *dir);

void			raycasting(t_info *info);
void			ray_minimap(t_player *p, t_vec2 *r_dir, double *dist,
		t_map *m_info);

int				read_file(char *file, t_info *info);
int				check_bounds(t_map *m_info);
t_img			*read_textures(void *mlx_ptr);

void			minimap(t_info *info);
void			pxl_to_img(t_img *img, int x, int y, int color);
void			fill_pixel(t_img *img, t_int2 a, t_int2 b, int color);

int				ft_strdelerr(char *line, int err_id);
int				splitdelerr(char **split, int err_id);
void			err_handler(int err_id);

int				splitlen(char **split);
void			splitdel(char **split);

void			draw_walls(t_int2 *col, double dist, int side, t_info *inf);
void			draw_tex_floor(t_int2 *col, double dist, t_info *inf);
void			draw_floor(t_int2 *col, t_info *inf);
void			draw_line(int x, int side, double dist, t_info *info);

void			show_usage(t_info *info);
int				close_win(void);

#endif
