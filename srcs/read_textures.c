/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:33:35 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/17 13:39:25 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "../libft/includes/libft.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "mlx.h"


#include <stdio.h>
int			error_exit(int msg)
{
	if (msg == MALLOC_ERR)
		write(1, "Error, could not allocate memory!\n", 34);
	else if (msg == READ_ERR)
		write(1, "An error occured while reading files!\n", 38);
	exit(EXIT_FAILURE);
}

t_img		*read_textures(void *mlx_ptr)
{
	t_img	*img;
	char	filename[256];
	int		i;

	if ((img = ft_memalloc(sizeof(t_img) * 4)) == NULL)
		error_exit(MALLOC_ERR);
	ft_bzero(filename, 256);
	ft_strcpy(filename, "textures/texture0.XPM");
	i = -1;
	while (++i < 4)
	{
		filename[16] = i + '0';
		img[i].img_ptr = mlx_xpm_file_to_image(mlx_ptr, filename,
				&img->width, &img->height);
		img[i].img_str = (int*)mlx_get_data_addr(img->img_ptr,
				&img->bpp, &img->sizel,
				&img->endian);
	}
	return (img);
}
