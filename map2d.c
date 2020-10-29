/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 11:34:58 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/29 10:48:18 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	draw_square(int i, int j, int color, t_all *all)
{
	int count_x;
	int count_y;
	int tmp;

	tmp = i;
	count_x = 0;
	count_y = 0;
	if (i > all->win_h || i > all->win_w || j > all->win_h || j > all->win_w)
		return ;
	while (count_y < SCALE)
	{
		count_x = 0;
		i = tmp;
		while (count_x < SCALE)
		{
			my_mlx_pixel_put(all, i++, j, color);
			count_x++;
		}
		j++;
		count_y++;
	}
}

void	draw_player(double i, double j, int color, t_all *all)
{
	int count_x;
	int count_y;
	int tmp;

	tmp = i;
	count_x = 0;
	count_y = 0;
	if (i > all->win_h || i > all->win_w || j > all->win_h || j > all->win_w)
		return ;
	while (count_y < SCALE)
	{
		count_x = 0;
		i = tmp;
		while (count_x < SCALE)
		{
			my_mlx_pixel_put(all, i++, j, color);
			count_x++;
		}
		j++;
		count_y++;
	}
}

void	draw_map(t_all *all)
{
	int j;
	int i;

	j = 0;
	while (all->s_map.map[j])
	{
		i = 0;
		while (all->s_map.map[j][i])
		{
			if (all->s_map.map[j][i] == '1')
				draw_square(i * SCALE, j * SCALE, 0x886B3D, all);
			else if (i == (int)all->plr.x && j == (int)all->plr.y)
				draw_player(all->plr.x * SCALE, all->plr.y * SCALE, 0x5E6B3D,\
				all);
			else if (all->s_map.map[j][i] == '2')
				draw_square(i * SCALE, j * SCALE, 0x655560, all);
			i++;
		}
		j++;
	}
}
