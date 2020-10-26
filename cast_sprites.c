/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 22:00:00 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/27 01:05:43 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	sort_sprites_2(int *spriteOrder, double *spriteDistance, int count)
{
	int		i;
	int		tmp_i;
	double	tmp_d;
	int		flag;
	// наверняка есть более оптимальный алгоритм сортировки!! Надо подумать!!!
	i = 0;
	flag = 1;
	while (flag)
	{
		flag = 0;
		i = 0;
		while (i < count)
		{
			if (spriteDistance[i] < spriteDistance[i + 1])
			{
				tmp_i = spriteOrder[i];
				spriteOrder[i] = spriteOrder[i + 1];
				spriteOrder[i + 1] = tmp_i;
				tmp_d = spriteDistance[i];
				spriteDistance[i] = spriteDistance[i + 1];
				spriteDistance[i + 1] = tmp_d;
				flag = 1;
			}
			i++;
		}
	}
}

void	sort_sprites(t_all *all, int *spriteOrder)
{
	int		i;
	double	spriteDistance[all->spr.spr_count];

	i = 0;
	while (i < all->spr.spr_count)
	{
		spriteOrder[i] = i;
		spriteDistance[i] = ((all->plr.x - all->spr.spr[i][1]) * (all->plr.x\
		- all->spr.spr[i][1]) + (all->plr.y - all->spr.spr[i][0]) *\
		(all->plr.y - all->spr.spr[i][0]));
		i++;
	}
	sort_sprites_2(spriteOrder, spriteDistance, all->spr.spr_count);
}

void	draw_sprites(t_all *all, double *buf)
{
	int i;
	int j;
	int k;
	int texX;
	int	texY;

	i = all->spr.drawStartX - 1;
	while (++i < all->spr.drawEndX)
	{
		texX = (int)(256 * (i - (-all->spr.spriteWidth / 2 +\
		all->spr.spriteScreenX)) * all->tex.tex_w[4] / all->spr.spriteWidth) / 256;
		if (all->spr.transformY > 0 && i > 0 && i < all->win_w &&\
		all->spr.transformY < buf[i])
		{
			j = all->spr.drawStartY - 1;
			while (++j < all->spr.drawEndY)
			{
				k = j * 256 - all->win_h * 128 + all->spr.spriteHeight * 128;
				texY = ((k * all->tex.tex_h[4]) / all->spr.spriteHeight) / 256;
				all->tex.color = all->tex.tex[4][all->tex.tex_h[4] * texY + texX];
				if (all->tex.color != 0x000000)
					my_mlx_pixel_put(all, i, j, all->tex.color);
			}
		}
	}
}

void	sprite_casting_part2(t_all *all, double *buf)
{
	all->spr.drawEndY = all->spr.spriteHeight / 2 + all->win_h / 2;
	if (all->spr.drawEndY >= all->win_h)
		all->spr.drawEndY = all->win_h - 1;
	all->spr.spriteWidth = abs((int)(all->win_h / all->spr.transformY));
	if (all->win_h - all->win_w > 500)
		all->spr.spriteWidth = abs((int)(all->win_w / all->spr.transformY));
	all->spr.drawStartX = -all->spr.spriteWidth / 2 + all->spr.spriteScreenX;
	if (all->spr.drawStartX < 0)
		all->spr.drawStartX = 0;
	all->spr.drawEndX = all->spr.spriteWidth / 2 + all->spr.spriteScreenX;
	if (all->spr.drawEndX >= all->win_w)
		all->spr.drawEndX = all->win_w - 1;
	draw_sprites(all, buf);
}

void	sprite_casting(t_all *all, double *buf)
{
	int	spriteOrder[all->spr.spr_count];
	int	i;

	i = 0;
	sort_sprites(all, spriteOrder);
	while (i < all->spr.spr_count)
	{
		all->spr.spriteX = all->spr.spr[spriteOrder[i]][1] + 0.5 - all->plr.x;
		all->spr.spriteY = all->spr.spr[spriteOrder[i]][0] + 0.5 - all->plr.y;
		all->spr.invDet = 1.0 / (all->plr.planeX * all->plr.dirY - all->plr.dirX\
		* all->plr.planeY);
		all->spr.transformX = all->spr.invDet * (all->spr.spriteX * all->plr.dirY\
		- all->plr.dirX * all->spr.spriteY);
		all->spr.transformY = all->spr.invDet * (all->plr.planeX * all->spr.spriteY -\
		all->spr.spriteX * all->plr.planeY);
		all->spr.spriteScreenX = (int)((all->win_w / 2) * (1 + all->spr.transformX\
		/ all->spr.transformY));
		all->spr.spriteHeight = abs((int)(all->win_h / all->spr.transformY));
		all->spr.drawStartY = -all->spr.spriteHeight / 2 + all->win_h / 2;
		if (all->spr.drawStartY < 0)
			all->spr.drawStartY = 0;
		sprite_casting_part2(all, buf);
		i++;
	}
	free(buf);
}