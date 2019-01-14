/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:40:31 by wta               #+#    #+#             */
/*   Updated: 2019/01/14 15:26:16 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
#include "wolf3d.h"

int		check_fmt(char *str)
{
	unsigned int	value;
	int				len;
	int				idx;

	if ((len = ft_strlen(str)) > 11)
		return (-1);
	idx = -1;
	while (++idx < len)
		if (str[idx] < '0' || str[idx] > '9')
			return (-1);
	if ((value = ft_atoi(str)) < 3)
		return (-1);
	return (value);
}



int		parse_first_line(char *str, t_map *map_info)
{
	char	**split;
	int		ret;
	int		len;

	ret = 1;
	if ((split = ft_strsplit(str, ' ')) != NULL && (len = splitlen(split) == 2)) // FORMAT : 2 ARGUMENTS -> WIDTH HEIGHT
	{
		
		map_info->width = check_fmt(split[0]);
		map_info->height = check_fmt(split[1]);
		if (map_info->width < 0 || map_info->height < 0)
			ret = 0;
	}
	else
		ret = 0;
	splitdel(split);
	return (ret);
}

int		prealloc_map(t_map *map_info)
{
	map_info->map = (char**)ft_memalloc(sizeof(char*) * (map_info->height + 1));
	return (map_info->map != NULL);
}

int		check_line(char *line, char *tokens, t_map *map_info)
{
	int	i;
	int	j;

	if ((int)ft_strlen(line) != map_info->width)
		return (0);
	i = -1;
	while (line[i++] != '\0')
	{
		j = -1;
		while (tokens[j] != '\0')
			if (line[i] != tokens[j])
				j++;
		if (tokens[j] == '\0')
			return (0);
	}
	return (1);
}

int		read_file(char *file, t_map *map_info)
{
	char	*line;
	int		line_count;
	int		gnl_ret;
	int		fn_ret;
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (-1);
	if (get_next_line(fd, &line) <= 0)
		return (GNL_ERR);
	if (parse_first_line(line, map_info) == 0)
		return (ft_strdelerr(line, BAD_FMT));
	ft_strdel(&line);
	if (prealloc_map(map_info) == 0)
		return (MALLOC_ERR);
	line_count = 0;
	fn_ret = 1;
	while (fn_ret == 1 && (gnl_ret = get_next_line(fd, &line)) > 0)
	{
		if (check_line(line, TOKENS, map_info) != 0)
			map_info->map[line_count] = line;
		else
			fn_ret = 0;
		line_count += 1;
	}
	close(fd);
	if (line_count != map_info->height || fn_ret == 0 || gnl_ret < 0)
		return (splitdelerr(map_info->map, (gnl_ret < 0) ? GNL_ERR : BAD_FMT));
	return (1);
}
