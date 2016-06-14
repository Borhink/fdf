/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhonore <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/11 11:49:57 by qhonore           #+#    #+#             */
/*   Updated: 2016/02/08 03:04:11 by qhonore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	launch_fdf(t_data *data, int ac)
{
	if (ac == 2)
		init_colors(&(data->pal), "-c,1B4FDC,FFFF66,1BDC1B,994C00,FFFFFF");
	data->proj = 1;
	mlx_key_hook(data->win, key_hook, (void*)data);
	mlx_expose_hook(data->win, expose_hook, (void*)data);
	mlx_loop(data->mlx);
}

int			main(int ac, char **av)
{
	t_data	data;
	int		fd;

	if (ac < 2 || ac > 3)
		ft_putendl("Usage : ./fdf map_file [-c]");
	else if (ac == 3 && !(init_colors(&(data.pal), av[2])))
		ft_putendl("-c usage : -c,ffffff,00ff00,ff0000,0000ff,000000");
	else if ((fd = open(av[1], O_RDONLY)) < 3)
		ft_putendl("Open failed.");
	else if (!(map_checker(fd, &(data.map))))
		ft_putendl("Creation of the map failed.");
	else if (!(data.mlx = mlx_init()))
		ft_putendl("Initialization of mlx failed.");
	else if (!(data.win = mlx_new_window(data.mlx, WIN_W, WIN_H, "FdF")))
		ft_putendl("Creation of the window failed.");
	else if (!(init_img(&data, &(data.img))))
		ft_putendl("Creation of the image failed.");
	else
		launch_fdf(&data, ac);
	return (0);
}
