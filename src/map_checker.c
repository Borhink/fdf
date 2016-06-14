/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 13:07:48 by qhonore           #+#    #+#             */
/*   Updated: 2016/02/06 14:53:54 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		fill_line(t_map *map, int x, int y, t_list **list)
{
	while (++x < map->wth)
		map->dot[y][x].y = 0;
	ft_lstndel(list, 1);
}

static t_coord	get_dimension(int fd, t_list **list)
{
	char	*line;
	char	**tab;
	t_coord	size;
	int		i;

	line = NULL;
	size = set_coord(0, 0);
	while (get_next_line(fd, &line))
	{
		i = 0;
		tab = ft_strsplit(line, ' ');
		while (tab[i])
			i++;
		if (!(ft_lstaddend(list, ft_lstnew(tab, sizeof(char*) * (i + 1)))))
			return (set_coord(-1, -1));
		free(line);
		if (size.x < i)
			size.x = i;
		size.y++;
	}
	close(fd);
	return (size);
}

int				map_checker(int fd, t_map *map)
{
	t_list	*list;
	t_coord	p;
	char	*tmp;
	int		connect;

	list = NULL;
	p.y = -1;
	connect = 0;
	if ((init_map(map, get_dimension(fd, &list))))
		while (list && ++p.y < map->hgt)
		{
			p.x = -1;
			while ((tmp = ((char**)list->content)[++p.x]))
			{
				if (ft_strisnb(tmp))
					map->dot[p.y][p.x].x = ft_atoi(tmp);
				map->dot[p.y][p.x].y = ft_strisnb(tmp) ? 1 : 0;
				if (map->dot[p.y][p.x].y && ((p.x && map->dot[p.y][p.x - 1].y)
							|| (p.y && map->dot[p.y - 1][p.x].y)))
					connect = 1;
				free(tmp);
			}
			fill_line(map, p.x - 1, p.y, &list);
		}
	return (connect);
}
