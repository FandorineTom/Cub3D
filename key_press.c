/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 23:24:28 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/25 23:30:16 by snorthmo         ###   ########.fr       */
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
	return (0);
}

int		close_win(int win)
{
	win = 0;
	exit(0);
}