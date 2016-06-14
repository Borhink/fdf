/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expose_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/05 00:56:03 by qhonore           #+#    #+#             */
/*   Updated: 2016/02/08 03:15:18 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	clear_img(t_img *i)
{
	t_coord p;
	int		pos;

	p.y = -1;
	while (++p.y < WIN_H)
	{
		p.x = -1;
		while (++p.x < WIN_W)
		{
			pos = (p.y * i->sl) + (p.x * i->bpp / 8);
			i->d[pos + 0] = 0;
			i->d[pos + 1] = 0;
			i->d[pos + 2] = 0;
		}
	}
}

/*
** ===================== iso_projection() =====================
** p : position dans la map du point A
** n : position a ajouter pour obtenir le point B (p + n = B)
** c : decalage pour le rendu iso
** par : parametre suplementaire pour les x et y
** alt : decalage pour l'altitude finale du point
** a et b : position finale des points a relier
** ============================================================
*/

static void	iso_projection(t_data *d, t_coord p, t_coord c, t_coord n)
{
	t_map		*m;
	t_coord		par;
	t_coord		a;
	t_coord		b;
	t_coord		alt;

	m = &(d->map);
	alt.x = m->dot[p.y][p.x].x * m->altz * m->dist / 20;
	alt.y = m->dot[p.y + n.y][p.x + n.x].x * m->altz * m->dist / 20;
	par.x = (WIN_W / 2 * d->proj) + m->dch - (m->wth * m->dist / 2);
	par.y = (WIN_H / 2) - alt.x + m->dcv - (m->hgt * m->dist / 2);
	a = set_coord((((p.x - p.y) * m->dist * d->proj) + par.x) / d->proj
			, ((p.x + p.y) * m->dist * d->proj / 2) + par.y);
	par.y = (WIN_H / 2) - alt.y + m->dcv - (m->hgt * m->dist / 2);
	b = set_coord((((p.x + c.x - p.y) * m->dist * d->proj) + par.x) / d->proj
			, ((p.x + c.y + p.y) * m->dist * d->proj / 2) + par.y);
	draw_line(d, a, b, set_vect(p, n));
}

int			expose_hook(void *data)
{
	t_coord	p;
	t_data	*d;
	t_map	*m;

	p = set_coord(-1, -1);
	d = (t_data*)data;
	m = &(d->map);
	clear_img(&(d->img));
	while (++p.y < m->hgt)
	{
		p.x = -1;
		while (++p.x < m->wth)
		{
			if (m->dot[p.y][p.x].y)
			{
				if (p.y && m->dot[p.y - 1][p.x].y)
					iso_projection(d, p, set_coord(1, -1), set_coord(0, -1));
				if (p.x && m->dot[p.y][p.x - 1].y)
					iso_projection(d, p, set_coord(-1, -1), set_coord(-1, 0));
			}
		}
	}
	mlx_clear_window(d->mlx, d->win);
	mlx_put_image_to_window(d->mlx, d->win, d->img.i, 0, 0);
	return (1);
}
