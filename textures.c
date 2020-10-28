/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 14:46:31 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 13:23:43 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	implement_textures(t_all *all)
{
	void	*t[5];
	int		i[3];

	if (!(t[0] = mlx_xpm_file_to_image(all->win.mlx, all->tex.w_tex,\
	&all->tex.tex_w[0], &all->tex.tex_h[0])))
		error_write(2);
	if (!(t[1] = mlx_xpm_file_to_image(all->win.mlx, all->tex.e_tex,\
	&all->tex.tex_w[1], &all->tex.tex_h[1])))
		error_write(2);
	if (!(t[2] = mlx_xpm_file_to_image(all->win.mlx, all->tex.n_tex,\
	&all->tex.tex_w[2], &all->tex.tex_h[2])))
		error_write(2);
	if (!(t[3] = mlx_xpm_file_to_image(all->win.mlx, all->tex.s_tex,\
	&all->tex.tex_w[3], &all->tex.tex_h[3])))
		error_write(2);
	if (!(t[4] = mlx_xpm_file_to_image(all->win.mlx, all->tex.spr_tex,\
	&all->tex.tex_w[4], &all->tex.tex_h[4])))
		error_write(2);
	all->tex.tex[0] = (int*)mlx_get_data_addr(t[0], &i[0], &i[1], &i[2]);
	all->tex.tex[1] = (int*)mlx_get_data_addr(t[1], &i[0], &i[1], &i[2]);
	all->tex.tex[2] = (int*)mlx_get_data_addr(t[2], &i[0], &i[1], &i[2]);
	all->tex.tex[3] = (int*)mlx_get_data_addr(t[3], &i[0], &i[1], &i[2]);
	all->tex.tex[4] = (int*)mlx_get_data_addr(t[4], &i[0], &i[1], &i[2]);
}

void	texturing_calculations(t_all *all, t_ray *ray)
{
	double	wallx;

	if (ray->side == 0)
		wallx = all->plr.y + ray->perp_wall_dist * ray->ray_diry;
	else
		wallx = all->plr.x + ray->perp_wall_dist * ray->ray_dirx;
	wallx -= floor((wallx));
	if (ray->side == 0)
	{
		if (ray->stepx < 0)
			all->tex.texx = (int)(wallx * (double)(all->tex.tex_w[0]));
		else
			all->tex.texx = (int)(wallx * (double)(all->tex.tex_w[1]));
	}
	else
	{
		if (ray->stepY < 0)
			all->tex.texx = (int)(wallx * (double)(all->tex.tex_w[2]));
		else
			all->tex.texx = (int)(wallx * (double)(all->tex.tex_w[3]));
	}
	if (ray->side == 1 && ray->ray_diry > 0)
		all->tex.texx = all->tex.tex_w[3] - all->tex.texx - 1;
	if (ray->side == 0 && ray->ray_dirx < 0)
		all->tex.texx = all->tex.tex_w[0] - all->tex.texx - 1;
}

void	draw_wall_part2(t_all *all, t_ray *ray, int x, int i)
{
	int texY;

	if (ray->stepY < 0)
	{
		texY = (int)all->tex.texpos & (all->tex.tex_h[2] - 1);
		all->tex.color = all->tex.tex[2][all->tex.tex_h[2] * texY + all->tex.texx];
		my_mlx_pixel_put(all, x, i, all->tex.color);
	}
	else
	{
		texY = (int)all->tex.texpos & (all->tex.tex_h[3] - 1);
		all->tex.color = all->tex.tex[3][all->tex.tex_h[3] * texY + all->tex.texx];
		my_mlx_pixel_put(all, x, i, all->tex.color);
	}
}

void	draw_wall(t_all *all, t_ray *ray, int x, int i)
{
	int	texY;

	all->tex.texpos += all->tex.step;
	if (ray->side == 0)
	{
		if (ray->stepx < 0)
		{
			texY = (int)all->tex.texpos & (all->tex.tex_h[0] - 1);
			all->tex.color = all->tex.tex[0][all->tex.tex_h[0] * texY + all->tex.texx];
			my_mlx_pixel_put(all, x, i, all->tex.color);
		}
		else
		{
			texY = (int)all->tex.texpos & (all->tex.tex_h[1] - 1);
			all->tex.color = all->tex.tex[1][all->tex.tex_h[1] * texY + all->tex.texx];
			my_mlx_pixel_put(all, x, i, all->tex.color);
		}
	}
	else
		draw_wall_part2(all, ray, x, i);
}

void	draw_floor(t_all *all, t_ray *ray, int x)
{
	int i;

	i = ray->drawend + 1;
	while (i < all->win_h)
	{
		my_mlx_pixel_put(all, x, i, all->tex.f_col);
		i++;
	}
}

void	draw_line(t_all *all, t_ray *ray, int x)
{
	int i;

	i = 0;
	if (ray->side == 0)
	{
		if (ray->stepx < 0)
			all->tex.step = 1.0 * all->tex.tex_h[0] / ray->line_height;
		else
			all->tex.step = 1.0 * all->tex.tex_h[1] / ray->line_height;
	}
	else
	{
		if (ray->stepY < 0)
			all->tex.step = 1.0 * all->tex.tex_h[2] / ray->line_height;
		else
			all->tex.step = 1.0 * all->tex.tex_h[3] / ray->line_height;
	}
	while (i < ray->draw_start)
		my_mlx_pixel_put(all, x, i++, all->tex.c_col);
	all->tex.texpos = (ray->draw_start - all->win_h / 2 + ray->line_height / 2)\
	* all->tex.step;
	i = ray->draw_start;
	while (i < ray->drawend)
		draw_wall(all, ray, x, i++);
	draw_floor(all, ray, x);
}