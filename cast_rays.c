/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:39 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 13:12:19 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <stdio.h>

void	cast_rays_part2(t_all *all, t_ray *ray)
{
	ray->ray_diry = all->plr.diry + all->plr.planey * ray->camerax;
	ray->mapx = (int)all->plr.x;
	ray->mapy = (int)all->plr.y;
	ray->delta_distx = fabs(1 / ray->ray_dirx);
	ray->delta_disty = fabs(1 / ray->ray_diry);
	if (ray->ray_dirx < 0)
	{
		ray->stepx = -1;
		ray->sideDistx = (all->plr.x - ray->mapx) * ray->delta_distx;
	}
	else
	{
		ray->stepx = 1;
		ray->sideDistx = (ray->mapx + 1.0 - all->plr.x) * ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->stepY = -1;
		ray->sideDisty = (all->plr.y - ray->mapy) * ray->delta_disty;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDisty = (ray->mapy + 1.0 - all->plr.y) * ray->delta_disty;
	}
}

void	line_start_end(t_all *all, t_ray *ray)
{
	ray->line_height = (int)(all->win_h / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + all->win_h / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->drawend = ray->line_height / 2 + all->win_h / 2;
	if (ray->drawend > all->win_h)
		ray->drawend = all->win_h - 1;
}

void	actual_dda(t_all *all, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistx < ray->sideDisty)
		{
			ray->sideDistx += ray->delta_distx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sideDisty += ray->delta_disty;
			ray->mapy += ray->stepY;
			ray->side = 1;
		}
		if (all->s_map.map[ray->mapy][ray->mapx] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->mapx - all->plr.x + (1 - ray->stepx)\
		/ 2) / ray->ray_dirx;
	else
		ray->perp_wall_dist = (ray->mapy - all->plr.y + (1 - ray->stepY)\
		/ 2) / ray->ray_diry;
	line_start_end(all, ray);
}

void	cast_rays(t_all *all)
{
	int		x;
	double	*buf;
	t_ray	ray;

	x = -1;
	if (!(buf = malloc(sizeof(double) * all->win_w)))
		error_write(5);
	if (all->flag)
		implement_textures(all);
	while (++x < all->win_w)
	{
		ray.camerax = 2 * x / (double)all->win_w - 1;
		ray.ray_dirx = all->plr.dirx + all->plr.planex * ray.camerax;
		cast_rays_part2(all, &ray);
		actual_dda(all, &ray);
		texturing_calculations(all, &ray);
		draw_line(all, &ray, x);
		buf[x] = ray.perp_wall_dist;
	}
	sprite_casting(all, buf);
	draw_map(all);
}
