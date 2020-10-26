/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 20:44:41 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/25 23:32:24 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

t_map	init_map(void)
{
	t_map	map;

	if (!(map.map_line = malloc(sizeof(char) * 1)))
		error_write(5);
	map.map_line[0] = '\0';
	return (map);
}

t_tex	init_tex(void)
{
	t_tex	tex;

	tex.n_tex = NULL;
	tex.s_tex = NULL;
	tex.e_tex = NULL;
	tex.w_tex = NULL;
	tex.spr_tex = NULL;
	tex.f_col = -1;
	tex.c_col = -1;
	tex.s_tmp = NULL;
	return (tex);
}

t_vars	init_win(void)
{
	t_vars	win;

	win.mlx = NULL;
	win.win = NULL;
	return (win);
}

t_spr	init_spr(void)
{
	t_spr	spr;

	spr.spr_count = 0;
	return (spr);
}

t_mov	init_mov(void)
{
	t_mov	mov;

	mov.m_speed = 0.07;
	mov.r_speed = 0.03;
	mov.w = 0;
	mov.s = 0;
	mov.a = 0;
	mov.d = 0;
	return (mov);
}

void	ft_init_all(t_all *all)
{
	t_plr	plr;

	plr.dirX = 0;
	plr.dirY = 0;
	all->s_map = init_map();
	all->tex = init_tex();
	all->win = init_win();
	all->spr = init_spr();
	all->mov = init_mov();
	all->plr = plr;
	all->win_w = 0;
	all->win_h = 0;
	all->win_h_max = 0;
	all->win_w_max = 0;
	all->flag = 1;
}