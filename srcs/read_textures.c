/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:33:35 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/16 17:26:14 by awoimbee         ###   ########.fr       */
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
	else
		write(1, "An error occured!\n", 18);
	exit(EXIT_FAILURE);
}

int			**read_textures(void *mlx_ptr)
{
	int		**textures;
	int		i;
	char	f_name[24];
	int		null;

	if (!(textures = (int**)malloc(sizeof(int*) * 4)))
		error_exit(MALLOC_ERR);
	ft_bzero(f_name, 24);
	ft_strcpy(f_name, "./textures/texture");
	ft_strcpy(f_name + 19, ".XPM");
	i = -1;
	while (++i < 4)
	{
		f_name[18] = i + '0';
		textures[i] = (int*)mlx_xpm_file_to_image(mlx_ptr, f_name, &null, &null);
		fprintf(stderr, "=>texture file: %s\theight = %d\n", f_name, null);
		if (textures[i] == 0)
			error_exit(READ_ERR);
		for (unsigned int j = 0; j < 640 * 640; ++j)
		{
			fprintf(stderr, "(%d, %d, %d)\t", (unsigned char)(textures[i][j] >> 16), (unsigned char)(textures[i][j] >> 8), (unsigned char)(textures[i][j]));
		}
		fprintf(stderr, "\n\n");
	}
	return (textures);
}
