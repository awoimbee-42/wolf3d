/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wta <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 12:40:31 by wta               #+#    #+#             */
/*   Updated: 2019/01/16 08:19:46 by wta              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

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

int		p_set(t_info *info)
{
	return (info->player.pos.x != -1 && info->player.pos.y != -1);
}

void	set_vec2(double x, double y, t_vec2 *pos)
{
	pos->x = x;
	pos->y = y;
}

int		check_line(char *line, int row, char *tokens, t_info *info)
{
	int	i;
	int	j;

	if ((int)ft_strlen(line) != info->m_info.width)
		return (0);
	i = -1;
	while (line[++i] != '\0')
	{
		j = -1;
		if (line[i] == '@' && p_set(info) == 0)
			set_vec2((double)i, (double)row, &info->player.pos);
		else if (line[i] == '@')
			return (0);
		else
		{
			while (tokens[++j] != '\0')
				if (line[i] == tokens[j])
					break ;
			if (tokens[j] == '\0')
				return (0);
		}
	}
	return (1);
}

int		read_file(char *file, t_info *info)
{
	char	*line;
	int		line_count;
	int		gnl_ret;
	int		ret;
	int		fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		return (-1);
	if (get_next_line(fd, &line) <= 0)
		return (GNL_ERR);
	if (parse_first_line(line, &info->m_info) == 0)
		return (ft_strdelerr(line, BAD_FMT));
	ft_strdel(&line);
	if (prealloc_map(&info->m_info) == 0)
		return (MALLOC_ERR);
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
		return (splitdelerr(info->m_info.map, (gnl_ret < 0) ? GNL_ERR : BAD_FMT));
	return (1);
}
