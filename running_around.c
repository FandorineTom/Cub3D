/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_around.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:59:34 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/27 14:26:06 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	front_back(t_all *all)
{
	if (all->mov.w)
	{
		if (all->s_map.map[(int)(all->plr.y)][(int)(all->plr.x +\
		all->plr.dirX * all->mov.m_speed)] == '0')
			all->plr.x += all->plr.dirX * all->mov.m_speed;
		if (all->s_map.map[(int)(all->plr.y + all->plr.dirY *\
		all->mov.m_speed)][(int)(all->plr.x)] == '0')
			all->plr.y += all->plr.dirY * all->mov.m_speed;
	}
	if (all->mov.s)
	{
		if (all->s_map.map[(int)(all->plr.y)][(int)(all->plr.x -\
		all->plr.dirX * all->mov.m_speed)] == '0')
			all->plr.x -= all->plr.dirX * all->mov.m_speed;
		if (all->s_map.map[(int)(all->plr.y - all->plr.dirY *\
		all->mov.m_speed)][(int)(all->plr.x)] == '0')
			all->plr.y -= all->plr.dirY * all->mov.m_speed;
	}
}

void	turning_left(t_all *all)
{
	double	tmp_dirX;
	double	tmp_planeX;

	if (all->mov.left)
	{
		tmp_dirX = all->plr.dirX;
		all->plr.dirX = all->plr.dirX * cos(-all->mov.r_speed) -\
						all->plr.dirY * sin(-all->mov.r_speed);
		all->plr.dirY = tmp_dirX * sin(-all->mov.r_speed) +\
						all->plr.dirY * cos(-all->mov.r_speed);
		tmp_planeX = all->plr.planeX;
		all->plr.planeX = all->plr.planeX * cos(-all->mov.r_speed) -\
						all->plr.planeY * sin(-all->mov.r_speed);
		all->plr.planeY = tmp_planeX * sin(-all->mov.r_speed) +\
						all->plr.planeY * cos(-all->mov.r_speed);
	}
}

void	left_right(t_all *all)
{
	if (all->mov.a)
	{
		if (all->s_map.map[(int)(all->plr.y)][(int)(all->plr.x +\
		all->plr.dirY * all->mov.m_speed)] == '0')
			all->plr.x += all->plr.dirY * all->mov.m_speed;
		if (all->s_map.map[(int)(all->plr.y - all->plr.dirX *\
		all->mov.m_speed)][(int)(all->plr.x)] == '0')
			all->plr.y -= all->plr.dirX * all->mov.m_speed;
	}
	if (all->mov.d)
	{
		if (all->s_map.map[(int)(all->plr.y)][(int)(all->plr.x -\
		all->plr.dirY * all->mov.m_speed)] == '0')
			all->plr.x -= all->plr.dirY * all->mov.m_speed;
		if (all->s_map.map[(int)(all->plr.y + all->plr.dirX *\
		all->mov.m_speed)][(int)(all->plr.x)] == '0')
			all->plr.y += all->plr.dirX * all->mov.m_speed;
	}
}

void	running_around(t_all *all)
{
	double	tmp_dirX;
	double	tmp_planeX;

	front_back(all);
	left_right(all);
	if (all->mov.right)
	{
		tmp_dirX = all->plr.dirX;
		all->plr.dirX = all->plr.dirX * cos(all->mov.r_speed) -\
						all->plr.dirY * sin(all->mov.r_speed);
		all->plr.dirY = tmp_dirX * sin(all->mov.r_speed) +\
						all->plr.dirY * cos(all->mov.r_speed);
		tmp_planeX = all->plr.planeX;
		all->plr.planeX = all->plr.planeX * cos(all->mov.r_speed) -\
						all->plr.planeY * sin(all->mov.r_speed);
		all->plr.planeY = tmp_planeX * sin(all->mov.r_speed) +\
						all->plr.planeY * cos(all->mov.r_speed);
	}
	turning_left(all);
}