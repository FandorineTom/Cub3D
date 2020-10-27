/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 19:45:30 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/28 00:17:00 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

void	check_cub_file(char *line, t_all *all)
{
	if ((ft_strnstr(line, "NO ", 3)) && all->tex.n_tex)
		error_write(7);
	else if ((ft_strnstr(line, "SO ", 3)) && all->tex.s_tex)
		error_write(7);
	else if ((ft_strnstr(line, "WE ", 3)) && all->tex.w_tex)
		error_write(7);
	else if ((ft_strnstr(line, "EA ", 3)) && all->tex.e_tex)
		error_write(7);
	else if ((ft_strnstr(line, "S ", 2)) && all->tex.spr_tex)
		error_write(7);
	else if ((ft_strnstr(line, "R ", 2)) && all->win_w)
		error_write(7);
	else if ((ft_strnstr(line, "F ", 2)) && all->tex.f_col != -1)
		error_write(7);
	else if ((ft_strnstr(line, "C ", 2)) && all->tex.c_col != -1)
		error_write(7);
	else if (all->s_map.map_line[0])
		error_write(7);
}

int		check_for_trash(char *s)
{
	while (*s == ' ' && *s)
		s++;
	while (*s != ' ' && *s)
		s++;
	while (*s == ' ' && *s)
		s++;
	if (*s)
		return (1);
	return (0);
}

void	check_for_commas(char *s)
{
	int i;

	i = 0;
	while(*s)
	{
		if (*s == ',')
			i++;
		s++;
	}
	if (i != 2)
		error_write(3);
}

void	check_valid_colors(char **s)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[i])
	{
		if (ft_atoi(s[i]) > 255 || ft_atoi(s[i]) < 0)
			error_write(3);
		i++;
	}
	if (i != 3)
		error_write(3);
	if ((tmp = ft_strchr(s[i - 1], ' ')))
	{
		while (*tmp)
		{
			if (*tmp != ' ')
				error_write(3);
			tmp++;
		}
	}
}

void	check_map_trash(char *line, t_all *all)
{
	static int i;

	if (all->s_map.map_line[0] && line[0] == '\0')
		i = 1;
	if ((*line == '1' || *line == '0') && i == 1)
		error_write(7);
}

void	another_map_check(t_all *all, int x, int y)
{
	player_validity(all);
	if (all->s_map.map[0][x] == '3' || all->s_map.map[0][x] == '4')
		error_write(4);
	if ((all->s_map.map[y][x] == '3' || all->s_map.map[y][x] == '4')\
	&& (all->s_map.map[y][x + 1] == '0' || all->s_map.map[y][x - 1] == '0'\
	|| all->s_map.map[y + 1][x] == '0' || all->s_map.map[y - 1][x] == '0'))
		error_write(4);
	if ((all->s_map.map[y][x] == '3' || all->s_map.map[y][x] == '4')\
	&& (!all->s_map.map[y][x + 1] || !all->s_map.map[y][x - 1]\
	|| !all->s_map.map[y + 1][x] || !all->s_map.map[y - 1][x]))
		error_write(4);
}

int		check_map(t_all *all)
{
	int x;
	int y;

	y = -1;
	map_validity(all);
	while (all->s_map.map[++y + 1])
	{
		x = 0;
		while (all->s_map.map[y][x])
		{
			another_map_check(all, x, y);
			if ((all->s_map.map[y][x] == '3' || all->s_map.map[y][x] == '2')\
			&& (all->s_map.map[y][x + 1] == ' ' || all->s_map.map[y][x - 1] == ' '\
			|| all->s_map.map[y + 1][x] == ' ' || all->s_map.map[y + 1][x] == ' '))
				return (0);
			x++;
		}
	}
	x = -1;
	while (all->s_map.map[y][++x])
		if (all->s_map.map[y][x] != ' ' && all->s_map.map[y][x] != '1'\
		&& all->s_map.map[y][x] != '0')
		return (0);
	return_player(all);
	sprites_and_player(all);
	return (1);
}