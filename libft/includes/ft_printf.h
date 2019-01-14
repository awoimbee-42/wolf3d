/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 09:35:40 by wta               #+#    #+#             */
/*   Updated: 2019/01/08 19:39:42 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"
# include <stdarg.h>

# define SHARP		0x1
# define ZERO		0x2
# define MINUS		0x4
# define SPACE		0x8
# define PLUS		0x10
# define CAPS		0x20
# define ACC		0x40
# define CHAR		0x80
# define SHORT		0x100
# define LONG		0x200
# define LLONG		0x400
# define OCTAL		0x800
# define HEX_L		0x1000
# define HEX_U		0x2000
# define HEX_PTR	0x4000
# define LDOUBLE	0x8000

typedef struct	s_lpf
{
	struct s_lpf	*next;
	int				flag;
	int				width;
	int				acc;
	int				ret;
	char			type;
	char			*str;
}				t_lpf;

int				ft_printf(const char *fmt, ...);

void			ft_print_all(t_lpf *lpf, int *ret);
t_lpf			*ft_pf_new(void);
t_lpf			*ft_lpf_append(t_lpf **lpf, t_lpf *node);
int				ft_parse_mod(t_lpf *node, char *fmt);
char			ft_parse_flag(t_lpf *node, char *fmt, int *index, va_list ap);
int				ft_is_arg(char c);
char			*ft_strspace(int len);
char			*ft_strzero(int len);
char			*ft_convert_s(char *str, t_lpf *node);
char			*ft_convert_c(int c, t_lpf *node);
char			*ft_convert_p(unsigned long ptr, t_lpf *node);
char			*ft_convert_per(int c, t_lpf *node);
char			*ft_convert_d(long long n, t_lpf *node);
char			*ft_convert_u(unsigned long long n, t_lpf *node);
char			*ft_convert_o(unsigned long long n, t_lpf *node);
char			*ft_convert_hex(unsigned long long n, t_lpf *node);
char			*ft_convert_f(long double n, t_lpf *node);

char			*ft_convert_typed(t_lpf *node, va_list ap);
char			*ft_convert_typeu(t_lpf *node, va_list ap);
char			*ft_convert_typeo(t_lpf *node, va_list ap);
char			*ft_convert_typex(t_lpf *node, va_list ap);
char			*ft_convert_typef(t_lpf *node, va_list ap);

char			*ft_strinsert(char *s1, char *s2, int index);
char			*ft_convert_acc(char *output, int len, t_lpf *node);
char			*ft_format(char *output, int len, t_lpf *node);
char			*ft_itoa_pf(long long n, t_lpf *node);

int				ft_abs(long long n);
int				ft_intlen_base_u(unsigned long long n, int base);

void			ft_rm_lst(t_lpf *lst);
long double		ft_pow(long double n, int pow);
long double		ft_flush_double(long double n);

#endif
