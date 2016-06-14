/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 22:27:54 by qhonore           #+#    #+#             */
/*   Updated: 2016/02/08 03:04:42 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	free_datas_and_quit(t_data *d)
{
	int		i;

	i = -1;
	mlx_destroy_image(d->mlx, d->img.i);
	mlx_destroy_window(d->mlx, d->win);
	while (++i < d->map.hgt)
		free(d->map.dot[i]);
	free(d->map.dot);
	exit(1);
}

int			key_hook(int key, void *data)
{
	t_data *d;

	d = (t_data*)data;
	if (key == 53)
		free_datas_and_quit(d);
	if (key >= 83 && key <= 92)
		d->map.altz = key - 82;
	else if (key == 123)
		d->map.dch -= 20;
	else if (key == 124)
		d->map.dch += 20;
	else if (key == 125)
		d->map.dcv += 20;
	else if (key == 126)
		d->map.dcv -= 20;
	else if (key == 69)
		d->map.dist += d->map.dist < 300 ? 2 : 0;
	else if (key == 78)
		d->map.dist -= d->map.dist > 2 ? 2 : 0;
	else if (key == 18 || key == 19)
		d->proj = (key == 18 ? 1 : 2);
	expose_hook(data);
	return (1);
}
