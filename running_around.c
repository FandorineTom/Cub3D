/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_around.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:59:34 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/25 20:49:48 by snorthmo         ###   ########.fr       */
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

	if (all->mov.a)
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

void	running_around(t_all *all)
{
	double	tmp_dirX;
	double	tmp_planeX;

	front_back(all);
	if (all->mov.d)
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