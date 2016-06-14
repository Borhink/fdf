/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/07 16:49:00 by qhonore           #+#    #+#             */
/*   Updated: 2016/04/20 16:44:28 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_rgb	set_rgb(int r, int g, int b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}

int		init_colors(t_palette *p, char *s)
{
	int		color;

	if (!s || ft_strlen(s) != 37 || s[9] != ',' || s[16] != ',' || s[23] != ','
		|| s[30] != ',' || s[0] != '-' || s[1] != 'c' || s[2] != ',')
		return (0);
	color = ft_atoi_base(s + 3, 16);
	p->c1 = set_rgb(color / 65536 % 256, color / 256 % 256, color % 256);
	color = ft_atoi_base(s + 10, 16);
	p->c2 = set_rgb(color / 65536 % 256, color / 256 % 256, color % 256);
	color = ft_atoi_base(s + 17, 16);
	p->c3 = set_rgb(color / 65536 % 256, color / 256 % 256, color % 256);
	color = ft_atoi_base(s + 24, 16);
	p->c4 = set_rgb(color / 65536 % 256, color / 256 % 256, color % 256);
	color = ft_atoi_base(s + 31, 16);
	p->c5 = set_rgb(color / 65536 % 256, color / 256 % 256, color % 256);
	return (1);
}

/*
** ======================== get_color() ========================
** cur : position actuelle dans l'image
** vect : positions dans l'image des points A et B
** p : positions dans la map des points A et B
** dist : distance dans l'image entre x: cur et B | y: A et B
** alt : altitude des points A et B
** =============================================================
*/

t_rgb	get_color(t_data *d, t_coord cur, t_vect vect, t_vect p)
{
	t_palette	*pal;
	t_coord		dist;
	t_coord		alt;
	int			calt;

	pal = &(d->pal);
	dist.x = ft_abs(cur.x - vect.b.x) + ft_abs(cur.y - vect.b.y);
	dist.y = ft_abs(vect.a.x - vect.b.x) + ft_abs(vect.a.y - vect.b.y);
	alt.x = d->map.dot[p.a.y][p.a.x].x * d->map.altz;
	alt.y = d->map.dot[p.a.y + p.b.y][p.a.x + p.b.x].x * d->map.altz;
	if (p.b.x == 0)
		calt = 50 * (alt.y + (((alt.x - alt.y) * dist.x) / dist.y));
	else
		calt = 50 * (alt.x + (((alt.y - alt.x) * dist.x) / dist.y));
	if (calt >= 4000)
		return (pal->c5);
	else if (calt >= 750)
		return (pal->c4);
	else if (calt >= 50)
		return (pal->c3);
	else if (calt >= 0)
		return (pal->c2);
	else
		return (pal->c1);
}
