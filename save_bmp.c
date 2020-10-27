/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 15:05:51 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/27 21:36:58 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_bmp	init_bmp(t_all *all)
{
	t_bmp bmp;

	bmp.type[0] = 0x42;
	bmp.type[1] = 0x4D;
	bmp.file_size = (54 + all->win_h * all->win_w) * 4;
	bmp.reserved = 0x00000000;
	bmp.offset = 0x36;
	bmp.dib = 40;
	bmp.image_w = all->win_w;
	bmp.image_h = -all->win_h;
	bmp.plane = 1;
	bmp.bpp = 32;
	bmp.compression = 0;
	bmp.raw_bitmap_size = 4 * all->win_h * all->win_w;
	bmp.x = 0;
	bmp.y = 0;
	bmp.colors_count = 0;
	bmp.important_colors = 0;
	return (bmp);
}

void	write_header(int fd, t_bmp *bmp)
{
	write(fd, &bmp->type, 2);
	write(fd, &bmp->file_size, 4);
	write(fd, &bmp->reserved, 4);
	write(fd, &bmp->offset, 4);
	write(fd, &bmp->dib, 4);
	write(fd, &bmp->image_w, 4);
	write(fd, &bmp->image_h, 4);
	write(fd, &bmp->plane, 2);
	write(fd, &bmp->bpp, 2);
	write(fd, &bmp->compression, 4);
	write(fd, &bmp->raw_bitmap_size, 4);
	write(fd, &bmp->x, 4);
	write(fd, &bmp->y, 4);
	write(fd, &bmp->colors_count, 4);
	write(fd, &bmp->important_colors, 4);
}

void	write_file(int fd, t_all *all)
{
	int		j;

	j = 0;
	while (j < all->win_h)
	{
		write(fd, all->win.addr, all->win_w * sizeof(int));
		all->win.addr += all->win.line_length;
		j++;
	}
}

void	save_bmp(t_all *all)
{
	int			fd;
	t_bmp		bmp;

	fd = open("cub3D.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	bmp = init_bmp(all);
	write_header(fd, &bmp);
	write_file(fd, all);
	close(fd);
	exit(0);
}