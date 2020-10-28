/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_around.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:59:34 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 13:21:46 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	front_back(t_all *all)
{
	if (all->mov.w)
	{
		if (all->s_map.map[(int)(all->plr.y)][(int)(all->plr.x +\
		all->plr.dirx * all->mov.m_speed)] == '0')
			all->plr.x += all->plr.dirx * all->mov.m_speed;
		if (all->s_map.map[(int)(all->plr.y + all->plr.diry *\
		all->mov.m_speed)][(int)(all->plr.x)] == '0')
			all->plr.y += all->plr.diry * all->mov.m_speed;
	}
	if (all->mov.s)
	{
		if (all->s_map.map[(int)(all->plr.y)][(int)(all->plr.x -\
		all->plr.dirx * all->mov.m_speed)] == '0')
			all->plr.x -= all->plr.dirx * all->mov.m_speed;
		if (all->s_map.map[(int)(all->plr.y - all->plr.diry *\
		all->mov.m_speed)][(int)(all->plr.x)] == '0')
			all->plr.y -= all->plr.diry * all->mov.m_speed;
	}
}

void	turning_left(t_all *all)
{
	double	tmp_dirx;
	double	tmp_planex;

	if (all->mov.left)
	{
		tmp_dirx = all->plr.dirx;
		all->plr.dirx = all->plr.dirx * cos(-all->mov.r_speed) -\
						all->plr.diry * sin(-all->mov.r_speed);
		all->plr.diry = tmp_dirx * sin(-all->mov.r_speed) +\
						all->plr.diry * cos(-all->mov.r_speed);
		tmp_planex = all->plr.planex;
		all->plr.planex = all->plr.planex * cos(-all->mov.r_speed) -\
						all->plr.planey * sin(-all->mov.r_speed);
		all->plr.planey = tmp_planex * sin(-all->mov.r_speed) +\
						all->plr.planey * cos(-all->mov.r_speed);
	}
}

void	left_right(t_all *all)
{
	if (all->mov.a)
	{
		if (all->s_map.map[(int)(all->plr.y)][(int)(all->plr.x +\
		all->plr.diry * all->mov.m_speed)] == '0')
			all->plr.x += all->plr.diry * all->mov.m_speed;
		if (all->s_map.map[(int)(all->plr.y - all->plr.dirx *\
		all->mov.m_speed)][(int)(all->plr.x)] == '0')
			all->plr.y -= all->plr.dirx * all->mov.m_speed;
	}
	if (all->mov.d)
	{
		if (all->s_map.map[(int)(all->plr.y)][(int)(all->plr.x -\
		all->plr.diry * all->mov.m_speed)] == '0')
			all->plr.x -= all->plr.diry * all->mov.m_speed;
		if (all->s_map.map[(int)(all->plr.y + all->plr.dirx *\
		all->mov.m_speed)][(int)(all->plr.x)] == '0')
			all->plr.y += all->plr.dirx * all->mov.m_speed;
	}
}

void	running_around(t_all *all)
{
	double	tmp_dirx;
	double	tmp_planex;

	front_back(all);
	left_right(all);
	if (all->mov.right)
	{
		tmp_dirx = all->plr.dirx;
		all->plr.dirx = all->plr.dirx * cos(all->mov.r_speed) -\
						all->plr.diry * sin(all->mov.r_speed);
		all->plr.diry = tmp_dirx * sin(all->mov.r_speed) +\
						all->plr.diry * cos(all->mov.r_speed);
		tmp_planex = all->plr.planex;
		all->plr.planex = all->plr.planex * cos(all->mov.r_speed) -\
						all->plr.planey * sin(all->mov.r_speed);
		all->plr.planey = tmp_planex * sin(all->mov.r_speed) +\
						all->plr.planey * cos(all->mov.r_speed);
	}
	turning_left(all);
}
