/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 18:53:11 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 13:20:58 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	textures(char *line, t_all *all)
{
	char	*tex;
	int		i;

	i = 0;
	while (*line == ' ')
		line++;
	check_cub_file(line, all);
	while (*line++ != ' ')
		i++;
	while (*line == ' ')
		line++;
	if (!(tex = ft_strtrim(line, " ")))
		return ;
	line = ft_to_the_start(line, 0, i);
	line = ft_to_the_start(line, 1, i);
	if (ft_strnstr(line, "SO ", 3))
		all->tex.s_tex = tex;
	else if (ft_strnstr(line, "NO ", 3))
		all->tex.n_tex = tex;
	else if (ft_strnstr(line, "WE ", 3))
		all->tex.w_tex = tex;
	else if (ft_strnstr(line, "EA ", 3))
		all->tex.e_tex = tex;
	else if (ft_strnstr(line, "S ", 2))
		all->tex.spr_tex = tex;
}

void	parse_colors(char *line, t_all *all)
{
	check_for_commas(line);
	if (ft_strnstr(line, "F ", 2))
	{
		line = line + 2;
		all->tex.s_tmp = ft_split(line, ',');
		check_valid_colors(all->tex.s_tmp);
		all->tex.f_col = ft_atoi(all->tex.s_tmp[0]) << 16;
		all->tex.f_col = all->tex.f_col | (ft_atoi(all->tex.s_tmp[1]) << 8);
		all->tex.f_col = all->tex.f_col | ft_atoi(all->tex.s_tmp[2]);
	}
	else if (ft_strnstr(line, "C ", 2))
	{
		line = line + 2;
		all->tex.s_tmp = ft_split(line, ',');
		check_valid_colors(all->tex.s_tmp);
		all->tex.c_col = ft_atoi(all->tex.s_tmp[0]) << 16;
		all->tex.c_col = all->tex.c_col | (ft_atoi(all->tex.s_tmp[1]) << 8);
		all->tex.c_col = all->tex.c_col | ft_atoi(all->tex.s_tmp[2]);
	}
	if (all->tex.s_tmp)
		ft_free(all->tex.s_tmp);
}

void	parse_rest(char *line, t_all *all)
{
	if (ft_strchr(line, '-'))
		return ;
	mlx_get_screen_size(all->win.mlx, &all->win_w_max, &all->win_h_max);
	check_cub_file(line, all);
	if (ft_strnstr(line, "R ", 2))
	{
		while (*line == 'R' || *line == ' ' || *line == '0')
			line++;
		all->win_w = ft_atoi(line);
		if (all->win_w > all->win_w_max || all->win_w < 0)
			all->win_w = all->win_w_max;
		while (*line != ' ')
			line++;
		all->win_h = ft_atoi(line);
		if (all->win_h > all->win_h_max || all->win_h < 0)
			all->win_h = all->win_h_max;
		if (check_for_trash(line) && all->win_h > 0)
			error_write(1);
	}
	if (ft_strnstr(line, "F ", 2) || ft_strnstr(line, "C ", 2))
		parse_colors(line, all);
}

void	read_map(char *line, t_all *all)
{
	char *tmp1;
	char *tmp2;

	if (!(tmp1 = ft_strjoin(line, "|\0")))
		error_write(5);
	tmp2 = all->s_map.map_line;
	if (!(all->s_map.map_line = ft_strjoin(all->s_map.map_line, tmp1)))
		error_write(5);
	free(tmp1);
	free(tmp2);
}

void	parse(char *line, t_all *all)
{
	while (*line == ' ')
		line++;
	if ((ft_strnstr(line, "NO ", 3)) || (ft_strnstr(line, "SO ", 3)) ||\
	(ft_strnstr(line, "WE ", 3)) || (ft_strnstr(line, "EA ", 3)) ||\
	(ft_strnstr(line, "S ", 2)))
	{
		textures(line, all);
		return ;
	}
	if ((ft_strnstr(line, "F ", 2)) || (ft_strnstr(line, "C ", 2)) ||\
	(ft_strnstr(line, "R ", 2)))
	{
		parse_rest(line, all);
		return ;
	}
	check_map_trash(line, all);
	if (*line == '1' || *line == '0')
	{
		while (*(line - 1) == ' ')
			line--;
		read_map(line, all);
		return ;
	}
	if (line[0])
		error_write(7);
}
