/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:33:35 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/15 16:02:38 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "../libft/includes/libft.h"
#include "..libft/includes/ft_printf.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

int			error_exit(int msg)
{
	if (msg == MALLOC_ERR)
		write(1, "Error, could not allocate memory!\n", 34);
	else if (msg == READ_ERR)
		write(1, "An error occured while reading files!\n", 38);
	exit(EXIT_FAILURE);
}

int		**read_textures(void *mlx_ptr)
{
	int			**textures;
	char		i;
	char		filename[256];
	int			fd;


	if (!(textures = (int**)malloc(sizeof(int*) * 4))
		|| !(filename = ft_strnew(12)))
		error_exit(MALLOC_ERR);
	ft_strcpy(filename, "./textures/");
	ft_strcpy(filename + 12, ".XPM");
	i = -1;
	while (++i < 4)
	{
		filename[11] = i + '0';
		texture[i] =
		(int*)mlx_xpm_file_to_image(mlx_ptr, filename, TEX_WIDTH, TEX_HEIGHT);
	}
}