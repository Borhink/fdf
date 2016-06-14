/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 00:17:17 by qhonore           #+#    #+#             */
/*   Updated: 2016/02/08 03:04:14 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include "libft.h"
# include "mlx.h"

# define WIN_W 1920
# define WIN_H 1080

typedef struct s_coord		t_coord;
typedef struct s_vect		t_vect;
typedef struct s_rgb		t_rgb;
typedef struct s_palette	t_palette;
typedef struct s_map		t_map;
typedef struct s_img		t_img;
typedef struct s_data		t_data;

struct	s_coord
{
	int		x;
	int		y;
};

struct	s_vect
{
	t_coord	a;
	t_coord b;
};

struct	s_rgb
{
	int		r;
	int		g;
	int		b;
};

struct	s_palette
{
	t_rgb	c1;
	t_rgb	c2;
	t_rgb	c3;
	t_rgb	c4;
	t_rgb	c5;
};

struct	s_map
{
	t_coord	**dot;
	int		dist;
	int		hgt;
	int		wth;
	int		altz;
	int		dch;
	int		dcv;
};

struct	s_img
{
	void	*i;
	char	*d;
	int		bpp;
	int		sl;
	int		edn;
};

struct	s_data
{
	void		*mlx;
	void		*win;
	t_img		img;
	t_map		map;
	t_palette	pal;
	int			proj;
};

t_coord	set_coord(int x, int y);
t_vect	set_vect(t_coord a, t_coord b);
t_rgb	set_rgb(int r, int g, int b);
int		init_map(t_map *map, t_coord dim);
int		init_img(t_data *data, t_img *img);
void	draw_line(t_data *data, t_coord a, t_coord b, t_vect p);
int		map_checker(int fd, t_map *map);
int		key_hook(int key, void *data);
int		expose_hook(void *data);
int		init_colors(t_palette *p, char *s);
t_rgb	get_color(t_data *d, t_coord cur, t_vect vect, t_vect p);

#endif
