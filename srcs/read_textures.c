/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:33:35 by awoimbee          #+#    #+#             */
/*   Updated: 2019/01/16 13:22:10 by awoimbee         ###   ########.fr       */
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

int			error_exit(int msg)
{
	if (msg == MALLOC_ERR)
		write(1, "Error, could not allocate memory!\n", 34);
	else if (msg == READ_ERR)
		write(1, "An error occured while reading files!\n", 38);
	exit(EXIT_FAILURE);
}

int			**read_textures(void *mlx_ptr)
{
	int		**textures;
	int		i;
	char	filename[17];
	int		null;

	if (!(textures = (int**)malloc(sizeof(int*) * 4)))
		error_exit(MALLOC_ERR);
	ft_bzero(filename, 17);
	ft_strcpy(filename, "./textures/");
	ft_strcpy(filename + 12, ".XPM");
	i = -1;
	while (++i < 4)
	{
		filename[11] = i + '0';
		textures[i] =
		(int*)mlx_xpm_file_to_image(mlx_ptr, filename, &null, &null);
	}
	return (textures);
}
