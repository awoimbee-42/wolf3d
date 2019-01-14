/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <wta@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 17:21:30 by wta               #+#    #+#             */
/*   Updated: 2018/12/02 16:45:56 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	unicode_four(int c, const int fd)
{
	unsigned char	mask;
	unsigned char	tmp;

	tmp = c >> 18 | 0xF0;
	write(fd, &tmp, 1);
	mask = tmp << 6;
	tmp = ((c >> 12) ^ mask) | 0x80;
	write(fd, &tmp, 1);
	mask = tmp << 6;
	tmp = ((c >> 6) ^ mask) | 0x80;
	write(fd, &tmp, 1);
	mask = tmp << 6;
	tmp = (c ^ mask) | 0x80;
	write(fd, &tmp, 1);
}

static void	unicode_three(int c, const int fd)
{
	unsigned char	mask;
	unsigned char	tmp;

	tmp = c >> 12 | 0xe0;
	write(fd, &tmp, 1);
	mask = tmp << 6;
	tmp = ((c >> 6) ^ mask) | 0x80;
	write(fd, &tmp, 1);
	mask = tmp << 6;
	tmp = (c ^ mask) | 0x80;
	write(fd, &tmp, 1);
}

static void	unicode_two(int c, const int fd)
{
	unsigned char	mask;
	unsigned char	tmp;

	tmp = c >> 6 | 0xc0;
	write(fd, &tmp, 1);
	mask = tmp << 6;
	tmp = (c ^ mask) | 0x80;
	write(fd, &tmp, 1);
}

void		ft_putchar_fd(int c, const int fd)
{
	if (c >> 16)
		unicode_four(c, fd);
	else if (c >> 11)
		unicode_three(c, fd);
	else if (c >> 7)
		unicode_two(c, fd);
	else
		write(fd, &c, 1);
}
