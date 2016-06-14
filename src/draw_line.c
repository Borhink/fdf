/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/16 10:19:00 by qhonore           #+#    #+#             */
/*   Updated: 2016/03/15 17:16:16 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	img_put_pixel(t_data *d, t_img *i, t_coord p, t_rgb c)
{
	int		pos;

	pos = (p.y * i->sl) + (p.x * i->bpp / 8);
	if (i->edn)
	{
		i->d[pos] = mlx_get_color_value(d->mlx, c.r);
		i->d[pos + 1] = mlx_get_color_value(d->mlx, c.g);
		i->d[pos + 2] = mlx_get_color_value(d->mlx, c.b);
	}
	else
	{
		i->d[pos] = mlx_get_color_value(d->mlx, c.b);
		i->d[pos + 1] = mlx_get_color_value(d->mlx, c.g);
		i->d[pos + 2] = mlx_get_color_value(d->mlx, c.r);
	}
}

static void	draw_x(t_data *d, t_vect vect, int inc, t_vect p)
{
	t_coord	diff;
	t_coord	cur;
	int		err;
	int		size;
	int		pos;

	cur = vect.a;
	err = ft_abs(vect.b.x - vect.a.x);
	diff = set_coord(err * 2, ft_abs((vect.b.y - vect.a.y)) * 2);
	size = ((WIN_H - 1) * d->img.sl) + (WIN_W * d->img.bpp / 8);
	while (cur.x <= vect.b.x)
	{
		pos = (cur.y * d->img.sl) + (cur.x * d->img.bpp / 8);
		if (pos > 0 && pos + 2 < size && cur.x >= 0
			&& (cur.x * d->img.bpp / 8) < d->img.sl)
			img_put_pixel(d, &(d->img), cur, get_color(d, cur, vect, p));
		if ((err -= diff.y) <= 0)
		{
			cur.y += inc;
			err += diff.x;
		}
		cur.x++;
	}
}

static void	draw_y(t_data *d, t_vect vect, int inc, t_vect p)
{
	t_coord	diff;
	t_coord	cur;
	int		err;
	int		size;
	int		pos;

	cur = vect.a;
	err = ft_abs(vect.b.y - vect.a.y);
	diff = set_coord(err * 2, ft_abs((vect.b.x - vect.a.x)) * 2);
	size = ((WIN_H - 1) * d->img.sl) + (WIN_W * d->img.bpp / 8);
	while ((inc == 1 && cur.y <= vect.b.y) || (inc == -1 && cur.y >= vect.b.y))
	{
		pos = (cur.y * d->img.sl) + (cur.x * d->img.bpp / 8);
		if (pos > 0 && pos + 2 < size && cur.x >= 0
			&& (cur.x * d->img.bpp / 8) < d->img.sl)
			img_put_pixel(d, &(d->img), cur, get_color(d, cur, vect, p));
		if ((err -= diff.y) <= 0)
		{
			cur.x++;
			err += diff.x;
		}
		cur.y += inc;
	}
}

void		draw_line(t_data *d, t_coord a, t_coord b, t_vect p)
{
	t_coord	diff;
	int		inc;

	if (b.x < a.x)
	{
		diff = a;
		a = b;
		b = diff;
	}
	diff = set_coord(ft_abs(b.x - a.x), ft_abs(b.y - a.y));
	inc = b.y < a.y ? -1 : 1;
	if (diff.x < diff.y)
		draw_y(d, set_vect(a, b), inc, p);
	else
		draw_x(d, set_vect(a, b), inc, p);
}
