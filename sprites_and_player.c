/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_and_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 01:03:20 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/26 14:03:21 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	parse_sprites_part2(t_all *all)
{
	int i;
	int j;
	int k;

	k = 0;
	j = 0;
	while (all->s_map.map[j])
	{
		i = 0;
		while (all->s_map.map[j][i])
		{
			if (all->s_map.map[j][i] == '2')
			{
				all->spr.spr[k][0] = j;
				all->spr.spr[k][1] = i;
				k++;
			}
			i++;
		}
		j++;
	}
}

void	parse_sprites(t_all *all, int m)
{
	int x;
	int y;

	y = 0;
	while(all->s_map.map[y])
	{
		x = 0;
		while (all->s_map.map[y][x])
		{
			if (all->s_map.map[y][x++] == '2')
				all->spr.spr_count++;
		}
		y++;
	}
	if (all->spr.spr_count > 10)
		error_write(4);
	else if (!(all->spr.spr = malloc(sizeof(int) * m)))
		error_write(5);
	y = -1;
	while (y++ < all->spr.spr_count)
		if (!(all->spr.spr[y] = malloc(sizeof(int) * 2)))
			error_write(5);
	parse_sprites_part2(all);
}

void	player_orientation_part2(t_all *all, int x, int y)
{
	if (all->s_map.map[y][x + 1] == ' ' || all->s_map.map[y][x - 1] == ' ' ||\
	all->s_map.map[y + 1][x] == ' ' || all->s_map.map[y - 1][x] == ' ')
		error_write(4);
	if (all->s_map.map[y][x] == 'W')
	{
		all->plr.dirX = -1;
		all->plr.dirY = 0;
		all->plr.planeX = 0;
		all->plr.planeY = -1;
	}
	if (all->s_map.map[y][x] == 'E')
	{
		all->plr.dirX = 1;
		all->plr.dirY = 0;
		all->plr.planeX = 0;
		all->plr.planeY = 1;
	}
	all->s_map.map[y][x] = '0';
}

void	player_orientation(t_all *all, int x, int y)
{
	all->plr.x = x + 0.5;
	all->plr.y = y + 0.5;
	if (all->s_map.map[y][x] == 'N')
	{
		all->plr.dirX = 0;
		all->plr.dirY = -1;
		all->plr.planeX = 1;
		all->plr.planeY = 0;
	}
	if (all->s_map.map[y][x] == 'S')
	{
		all->plr.dirX = 0;
		all->plr.dirY = 1;
		all->plr.planeX = -1;
		all->plr.planeY = 0;
	}
	player_orientation_part2(all, x, y);
}

void	sprites_and_player(t_all *all)
{
	int		x;
	int		y;
	char	t;

	y = 0;
	while (*all->s_map.map[y])
	{
		x = 0;
		while(all->s_map.map[y][x])
		{
			t = all->s_map.map[y][x];
			if (t == 'N' || t == 'S' || t == 'W' || t == 'E')
				break ;
			x++;
		}
		if (t == 'N' || t == 'S' || t == 'W' || t == 'E')
		{
			player_orientation(all, x, y);
			break ;
		}
		y++;
	}
	parse_sprites(all, x);
}