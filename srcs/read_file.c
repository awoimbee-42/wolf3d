/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: awoimbee <awoimbee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:40:31 by wta               #+#    #+#             */
/*   Updated: 2019/01/19 23:33:06 by awoimbee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "wolf3d.h"

/*
**	check_fmt:
**		check the format of the map width and map height values
*/

static int	check_fmt(char *str)
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

/*
**	parse_first_line:
**	 The first line of map files should contain only
**		the width and height of said map
*/

static int	parse_first_line(char *str, t_map *map_info)
{
	char			**split;
	int				ret;
	int				len;

	ret = 1;
	if ((split = ft_strsplit(str, ' ')) != NULL
	&& (len = splitlen(split) == 2))
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

static int	prealloc_map(t_map *map_info)
{
	map_info->map = (char**)ft_memalloc(sizeof(char*) * (map_info->height + 1));
	return (map_info->map != NULL);
}

static int	check_line(char *line, int row, char *tokens, t_info *info)
{
	int				i;
	int				j;

	if ((int)ft_strlen(line) != info->m_info.width)
		return (0);
	i = -1;
	while (line[++i] != '\0')
	{
		if (line[i] == '@')
		{
			if (info->player.pos.x != -1 && info->player.pos.y != -1)
				return (0);
			line[i] = '0';
			info->player.pos = (t_vec2){((double)i) + .5, ((double)row) + .5};
		}
		else
		{
			j = -1;
			while (tokens[++j] != line[i])
				if (tokens[j] == '\0')
					return (0);
		}
	}
	return (1);
}

int			read_file(char *file, t_info *info)
{
	char			*line;
	int				line_count;
	int				gnl_ret;
	int				ret;
	int				fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (-1);
	get_next_line(fd, &line) <= 0 ? err_handler(GNL_ERR) : 0;
	!parse_first_line(line, &info->m_info) ?
		err_handler(ft_strdelerr(line, BAD_FMT)) : 0;
	ft_strdel(&line);
	!prealloc_map(&info->m_info) ? err_handler(MALLOC_ERR) : 0;
	line_count = 0;
	ret = 1;
	while (ret == 1 && (gnl_ret = get_next_line(fd, &line)) > 0)
	{
		if ((ret = check_line(line, line_count, TOKENS, info)) != 0)
			info->m_info.map[line_count] = line;
		line_count += 1;
	}
	close(fd);
	if (line_count != info->m_info.height || ret == 0 || gnl_ret < 0)
		return (splitdelerr(info->m_info.map, gnl_ret < 0 ? GNL_ERR : BAD_FMT));
	return (info->player.pos.x == -1 ? BAD_FMT : 1);
}
