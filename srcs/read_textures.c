/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:33:35 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/23 17:28:09 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int			error_exit(int msg)
{
	if (msg == MALLOC_ERR)
		write(1, "Error, could not allocate memory!\n", 34);
	else if (msg == READ_ERR)
		write(1, "An error occured while reading files!\n", 38);
	else
		write(1, "An error occured!\n", 18);
	exit(EXIT_FAILURE);
}

void		set_null(t_img *img)
{
	write(1, "Texture missing, replacing it with random color\n", 48);
	img->img_str = (int*)(&img->img_str);
	img->width = 1;
	img->height = 1;
}

t_img		*read_textures(void *mlx_ptr)
{
	t_img	*img;
	char	filename[256];
	int		i;

	if ((img = ft_memalloc(sizeof(t_img) * 6)) == NULL)
		error_exit(MALLOC_ERR);
	ft_bzero(filename, 256);
	ft_strcpy(filename, "textures/texture0.XPM");
	i = -1;
	while (++i < 6)
	{
		filename[16] = i + '0';
		img[i].img_ptr = mlx_xpm_file_to_image(mlx_ptr, filename,
				&img[i].width, &img[i].height);
		if (img[i].img_ptr != NULL)
			img[i].img_str = (int*)mlx_get_data_addr(img[i].img_ptr,
					&img[i].bpp, &img[i].sizel, &img[i].endian);
		else
			set_null(&img[i]);
	}
	return (img);
}
