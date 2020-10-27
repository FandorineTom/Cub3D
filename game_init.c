/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:34:18 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/27 15:05:22 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include "stdio.h"

void	ft_read_file(t_all *all, char *s)
{
	char	*line;
	int		fd;

	if (!(line = ft_strchr(s, '.')))
		error_write(8);
	if (ft_memcmp(line, ".cub", ft_strlen(line)))
		error_write(6);
	fd = open (s, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		parse(line, all);
		free(line);
	}
	parse(line, all);
	free(line);
	if (!all->s_map.map_line[0])
		error_write(4);
	all->s_map.map = ft_split(all->s_map.map_line, '|');
	if (!all->flag || all->tex.f_col == -1 || all->tex.c_col == -1)
		error_write(3);
	if (!all->win_h || !all->win_w)
		error_write(1);
	if (!(check_map(all)))
		error_write(4);
}

int		put_frame(t_all *all)
{
	if (!(all->mov.w || all->mov.a || all->mov.s || all->mov.d || all->mov.right || all->mov.left))
		return (0);
	running_around(all);
	all->win.img = mlx_new_image(all->win.mlx, all->win_w, all->win_h);
	all->win.addr = mlx_get_data_addr(all->win.img, &all->win.bits_per_pixel, &all->win.line_length, &all->win.endian);
	cast_rays(all);
	mlx_put_image_to_window(all->win.mlx, all->win.win, all->win.img, 0, 0);
	mlx_destroy_image(all->win.mlx, all->win.img);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	all;

	if (argc < 2 || argc > 3 || (argv[2] && (ft_strncmp(argv[2], "--save", 7))))
		error_write(9);
	ft_init_all(&all);
	ft_read_file(&all, argv[1]);
	all.win.mlx = mlx_init();
	all.win.win = mlx_new_window(all.win.mlx, all.win_w, all.win_h, "CUB3D");
	running_around(&all);
	all.win.img = mlx_new_image(all.win.mlx, all.win_w, all.win_h);
	all.win.addr = mlx_get_data_addr(all.win.img, &all.win.bits_per_pixel, &all.win.line_length, &all.win.endian);
	cast_rays(&all);
	if (argv[2] && !(ft_strncmp(argv[2], "--save", 7)))
		save_bmp(&all);
	all.flag = 0;
	mlx_put_image_to_window(all.win.mlx, all.win.win, all.win.img, 0, 0);
	mlx_destroy_image(all.win.mlx, all.win.img);
	mlx_loop_hook(all.win.mlx, put_frame, &all);
	mlx_hook(all.win.win, 2, (1L << 0), key_press, &all);
	mlx_hook(all.win.win, 3, (1L << 1), key_release, &all);
	mlx_hook(all.win.win, 17, 0, close_win, &all);
	mlx_loop(all.win.mlx);
}