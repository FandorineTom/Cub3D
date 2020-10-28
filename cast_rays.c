/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:35:39 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 12:11:52 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"
#include <stdio.h>

void	cast_rays_part2(t_all *all, t_ray *ray)
{
	ray->ray_dirY = all->plr.dirY + all->plr.planeY * ray->cameraX;
	ray->mapX = (int)all->plr.x;
	ray->mapY = (int)all->plr.y;
	ray->deltaDistX = fabs(1 / ray->ray_dirX);
	ray->deltaDistY = fabs(1 / ray->ray_dirY);
	if (ray->ray_dirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (all->plr.x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - all->plr.x) * ray->deltaDistX;
	}
	if (ray->ray_dirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (all->plr.y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - all->plr.y) * ray->deltaDistY;
	}
	
}

void	line_start_end(t_all *all, t_ray *ray)
{
	ray->lineHeight = (int)(all->win_h / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + all->win_h / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + all->win_h / 2;
	if (ray->drawEnd > all->win_h)
		ray->drawEnd = all->win_h - 1;
}

void	actual_dda(t_all *all, t_ray *ray)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (all->s_map.map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - all->plr.x + (1 - ray->stepX) / 2) / ray->ray_dirX;
	else
		ray->perpWallDist = (ray->mapY - all->plr.y + (1 - ray->stepY) / 2) / ray->ray_dirY;
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
		ray.cameraX = 2 * x / (double)all->win_w - 1;
		ray.ray_dirX = all->plr.dirX + all->plr.planeX * ray.cameraX;
		cast_rays_part2(all, &ray);
		actual_dda(all, &ray);
		texturing_calculations(all, &ray);
		draw_line(all, &ray, x);
		buf[x] = ray.perpWallDist;
	}
	sprite_casting(all, buf);
	draw_map(all);
}