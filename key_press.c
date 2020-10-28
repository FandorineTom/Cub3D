/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 23:24:28 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 15:34:57 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

int		key_press(int key, t_all *all)
{
	if (key == 53)
		exit(0);
	if (key == 13)
		all->mov.w = 1;
	if (key == 1)
		all->mov.s = 1;
	if (key == 0)
		all->mov.a = 1;
	if (key == 2)
		all->mov.d = 1;
	if (key == 123)
		all->mov.left = 1;
	if (key == 124)
		all->mov.right = 1;
	return (0);
}

int		key_release(int key, t_all *all)
{
	if (key == 13)
		all->mov.w = 0;
	if (key == 1)
		all->mov.s = 0;
	if (key == 0)
		all->mov.a = 0;
	if (key == 2)
		all->mov.d = 0;
	if (key == 123)
		all->mov.left = 0;
	if (key == 124)
		all->mov.right = 0;
	return (0);
}

int		close_win(int win)
{
	(void)win;
	exit(0);
}

t_map	init_map(void)
{
	t_map	map;

	if (!(map.map_line = malloc(sizeof(char) * 1)))
		error_write(5);
	map.map_line[0] = '\0';
	return (map);
}

void	check_map_trash(char *line, t_all *all)
{
	static int i;

	if (all->s_map.map_line[0] && line[0] == '\0')
		i = 1;
	if ((*line == '1' || *line == '0') && i == 1)
		error_write(7);
}
