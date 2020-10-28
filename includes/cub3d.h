/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:44:10 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 11:53:31 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../libft/libft.h"
# include "../mlx/mlx.h"

#define SCALE 5

typedef struct s_tex
{
	char		*n_tex;
	char		*s_tex;
	char		*e_tex;
	char		*w_tex;
	char		*spr_tex;
	int			f_col;
	int			c_col;
	int			tex_h[5];
	int			tex_w[5];
	int			*tex[5];
	int			texX;
	double		step;
	double		texPos;
	int			color;
	char		**s_tmp;
}				t_tex;

typedef struct	s_vars
{
	void		*mlx;
	void		*win;
	char		*addr;
	void		*img;
	int         bits_per_pixel;
    int         line_length;
	int			endian;
}				t_vars;

typedef struct	s_map
{
	char		**map;
	char		*map_line;
}				t_map;

typedef struct	s_plr
{
	double		x;
	double		y;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
}				t_plr;

typedef struct	s_spr
{
	int			spr_count;
	int			**spr;
	double		spriteX;
	double		spriteY;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			spriteHeight;
	int			spriteWidth;
	int			drawStartX;
	int			drawStartY;
	int			drawEndX;
	int			drawEndY;
}				t_spr;

typedef struct	s_mov
{
	double		m_speed;
	double		r_speed;
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_mov;

typedef struct	s_ray
{
	double		cameraX;
	double		ray_dirX;
	double		ray_dirY;
	int			mapX;
	int			mapY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
}				t_ray;

typedef	struct	s_bmp
{
	int			file_size;
	char		type[2];
	int			reserved;
	int			offset;
	int			dib;
	int			image_w;
	int			image_h;
	int			plane;
	int			bpp;
	int			compression;
	int			raw_bitmap_size;
	int			x;
	int			y;
	int			colors_count;
	int			important_colors;
}				t_bmp;

typedef struct	s_all
{
	t_tex		tex;
	t_vars		win;
	t_map		s_map;
	t_plr		plr;
	t_spr		spr;
	t_mov		mov;
	int			win_h;
	int			win_h_max;
	int			win_w;
	int			win_w_max;
	int			flag;
}				t_all;

void			error_write(int i);
void			check_cub_file(char *line, t_all *all);
int				check_for_trash(char *s);
void			parse(char *line, t_all *all);
void			check_for_commas(char *s);
void			ft_free(char **s);
void			ft_init_all(t_all *all);
void			check_valid_colors(char **s);
void			player_validity(t_all *all);
void			map_validity(t_all *all);
void			return_player(t_all *all);
void			sprites_and_player(t_all *all);
int				check_map(t_all *all);
char			*ft_to_the_start(char *line, int x, int y);
void			check_valid_colors(char **s);
void			check_map_trash(char *line, t_all *all);
void			running_around(t_all *all);
int				key_press(int key, t_all *all);
int				key_release(int key, t_all *all);
int				close_win(int win);
void			cast_rays(t_all *all);
void			implement_textures(t_all *all);
void			my_mlx_pixel_put(t_all *all, int x, int y, int color);
void			draw_line(t_all *all, t_ray *ray, int x);
void			texturing_calculations(t_all *all, t_ray *ray);
void			sprite_casting(t_all *all, double *buf);
t_map			init_map(void);
void			save_bmp(t_all *all);
void			draw_map(t_all *all);

#endif