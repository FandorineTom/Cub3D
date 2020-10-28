/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 22:00:00 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 14:08:18 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	sort_sprites_2(int *sprite_order, double *sprite_distance, int count)
{
	int		i;
	int		tmp_i;
	double	tmp_d;
	int		flag;

	flag = 1;
	while (flag)
	{
		flag = 0;
		i = 0;
		while (i < count)
		{
			if (sprite_distance[i] < sprite_distance[i + 1])
			{
				tmp_i = sprite_order[i];
				sprite_order[i] = sprite_order[i + 1];
				sprite_order[i + 1] = tmp_i;
				tmp_d = sprite_distance[i];
				sprite_distance[i] = sprite_distance[i + 1];
				sprite_distance[i + 1] = tmp_d;
				flag = 1;
			}
			i++;
		}
	}
}

void	sort_sprites(t_all *all, int *sprite_order)
{
	int		i;
	double	sprite_distance[all->spr.spr_count];

	i = 0;
	while (i < all->spr.spr_count)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((all->plr.x - all->spr.spr[i][1]) * (all->plr.x\
		- all->spr.spr[i][1]) + (all->plr.y - all->spr.spr[i][0]) *\
		(all->plr.y - all->spr.spr[i][0]));
		i++;
	}
	sort_sprites_2(sprite_order, sprite_distance, all->spr.spr_count);
}

void	draw_sprites(t_all *all, double *buf, int k)
{
	int i;
	int j;
	int texx;
	int	texy;

	i = all->spr.draw_startx - 1;
	while (++i < all->spr.draw_endx)
	{
		texx = (int)(256 * (i - (-all->spr.spr_w / 2 +\
	all->spr.spr_screenx)) * all->tex.tex_w[4] / all->spr.spr_w) / 256;
		if (all->spr.transformy > 0 && i > 0 && i < all->win_w &&\
		all->spr.transformy < buf[i])
		{
			j = all->spr.draw_starty - 1;
			while (++j < all->spr.draw_endy)
			{
				k = j * 256 - all->win_h * 128 + all->spr.spr_h * 128;
				texy = ((k * all->tex.tex_h[4]) / all->spr.spr_h) / 256;
				all->tex.color = all->tex.tex[4][all->tex.tex_h[4] *\
				texy + texx];
				if (all->tex.color != 0x000000)
					my_mlx_pixel_put(all, i, j, all->tex.color);
			}
		}
	}
}

void	sprite_casting_part2(t_all *all, double *buf)
{
	int k;

	k = 0;
	all->spr.draw_endy = all->spr.spr_h / 2 + all->win_h / 2;
	if (all->spr.draw_endy >= all->win_h)
		all->spr.draw_endy = all->win_h - 1;
	all->spr.spr_w = abs((int)(all->win_h / all->spr.transformy));
	if (all->win_h - all->win_w > 500)
		all->spr.spr_w = abs((int)(all->win_w / all->spr.transformy));
	all->spr.draw_startx = -all->spr.spr_w / 2 + all->spr.spr_screenx;
	if (all->spr.draw_startx < 0)
		all->spr.draw_startx = 0;
	all->spr.draw_endx = all->spr.spr_w / 2 + all->spr.spr_screenx;
	if (all->spr.draw_endx >= all->win_w)
		all->spr.draw_endx = all->win_w - 1;
	draw_sprites(all, buf, k);
}

void	sprite_casting(t_all *all, double *buf)
{
	int	sprite_order[all->spr.spr_count];
	int	i;

	i = 0;
	sort_sprites(all, sprite_order);
	while (i < all->spr.spr_count)
	{
		all->spr.sprx = all->spr.spr[sprite_order[i]][1] + 0.5 - all->plr.x;
		all->spr.spry = all->spr.spr[sprite_order[i]][0] + 0.5 - all->plr.y;
		all->spr.invdet = 1.0 / (all->plr.planex * all->plr.diry -\
		all->plr.dirx * all->plr.planey);
		all->spr.transformx = all->spr.invdet * (all->spr.sprx * all->plr.diry\
		- all->plr.dirx * all->spr.spry);
		all->spr.transformy = all->spr.invdet * (all->plr.planex *\
		all->spr.spry - all->spr.sprx * all->plr.planey);
		all->spr.spr_screenx = (int)((all->win_w / 2) * (1 +\
		all->spr.transformx / all->spr.transformy));
		all->spr.spr_h = abs((int)(all->win_h / all->spr.transformy));
		all->spr.draw_starty = -all->spr.spr_h / 2 + all->win_h / 2;
		if (all->spr.draw_starty < 0)
			all->spr.draw_starty = 0;
		sprite_casting_part2(all, buf);
		i++;
	}
	free(buf);
}
