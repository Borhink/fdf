/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 12:15:31 by qhonore           #+#    #+#             */
/*   Updated: 2016/02/07 16:56:27 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_coord	set_coord(int x, int y)
{
	t_coord	coord;

	coord.x = x;
	coord.y = y;
	return (coord);
}

t_vect	set_vect(t_coord a, t_coord b)
{
	t_vect	vect;

	vect.a = a;
	vect.b = b;
	return (vect);
}

int		init_map(t_map *map, t_coord dim)
{
	map->dist = 20;
	map->altz = 1;
	map->dch = 0;
	map->dcv = 0;
	map->hgt = dim.y;
	map->wth = dim.x;
	if (dim.x < 1 || dim.y < 1)
		return (0);
	if (!(map->dot = (t_coord**)malloc(sizeof(t_coord*) * dim.y)))
		return (0);
	while (--(dim.y) >= 0)
		if (!(map->dot[dim.y] = (t_coord*)malloc(sizeof(t_coord) * dim.x)))
			return (0);
	return (1);
}

int		init_img(t_data *data, t_img *img)
{
	if (!(img->i = mlx_new_image(data->mlx, WIN_W, WIN_H)))
		return (0);
	img->d = mlx_get_data_addr(img->i, &(img->bpp), &(img->sl), &(img->edn));
	return (1);
}
