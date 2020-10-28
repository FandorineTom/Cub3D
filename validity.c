/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 23:59:31 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 15:15:25 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <stdio.h>

void	map_validity(t_all *all)
{
	int		x;
	int		y;
	int		player;
	int		t;

	y = -1;
	player = 0;
	if (!all->s_map.map)
		error_write(5);
	while (all->s_map.map[++y])
	{
		x = 0;
		while (all->s_map.map[y][x])
		{
			t = all->s_map.map[y][x++];
			if (t != ' ' && t != '1' && t != '0' && t != '2' && t != 'N'
				&& t != 'W' && t != 'E' && t != 'S')
				error_write(4);
			if (t == 'W' || t == 'S' || t == 'E' || t == 'N')
				player++;
		}
	}
	if (player != 1)
		error_write(4);
}

void	walls_validity(char **map, int x, int y)
{
	int j;
	int i;

	i = 0;
	while (map[i])
		i++;
	if (y > 0 && map[y] && x > 0)
		j = ft_strlen(map[y]);
	else
		return ;
	if (y < 0 || y >= i || x < 0 || x >= j)
		error_write(4);
	if (map[y][x] == '1' || map[y][x] == '3' || map[y][x] == ' '
		|| map[y][x] == '4' || !map[y][x])
		return ;
	if (map[y][x] == '0')
		map[y][x] = '3';
	if (map[y][x] == '2')
		map[y][x] = '4';
	walls_validity(map, x, y + 1);
	walls_validity(map, x, y - 1);
	walls_validity(map, x + 1, y);
	walls_validity(map, x - 1, y);
}

void	player_validity(t_all *all)
{
	int		x;
	int		y;
	char	t;

	y = -1;
	while (all->s_map.map[++y])
	{
		x = 0;
		while (all->s_map.map[y][x])
		{
			t = all->s_map.map[y][x];
			if (t == 'N' || t == 'S' || t == 'W' || t == 'E')
				break ;
			x++;
		}
		if (t == 'N' || t == 'S' || t == 'W' || t == 'E')
		{
			if (y == 0)
				error_write(4);
			all->s_map.map[y][x] = '0';
			walls_validity(all->s_map.map, x, y);
			all->s_map.map[y][x] = t;
			break ;
		}
	}
}

void	return_walls(char **map, int x, int y)
{
	int j;
	int i;

	i = 0;
	while (map[i])
		i++;
	j = ft_strlen(map[y]);
	if (y < 0 || y >= i || x < 0 || y >= j)
		error_write(4);
	if (map[y][x] == '1' || map[y][x] == '0' || map[y][x] == ' '\
	|| map[y][x] == '2')
		return ;
	if (map[y][x] == '3')
		map[y][x] = '0';
	if (map[y][x] == '4')
		map[y][x] = '2';
	return_walls(map, x, y + 1);
	return_walls(map, x, y - 1);
	return_walls(map, x + 1, y);
	return_walls(map, x - 1, y);
}

void	return_player(t_all *all)
{
	int		x;
	int		y;
	char	t;

	y = 0;
	while (all->s_map.map[y])
	{
		x = 0;
		while (all->s_map.map[y][x])
		{
			t = all->s_map.map[y][x];
			if (t == 'N' || t == 'S' || t == 'W' || t == 'E')
				break ;
			x++;
		}
		if (t == 'N' || t == 'S' || t == 'W' || t == 'E')
		{
			all->s_map.map[y][x] = '3';
			return_walls(all->s_map.map, x, y);
			all->s_map.map[y][x] = t;
			break ;
		}
		y++;
	}
}
