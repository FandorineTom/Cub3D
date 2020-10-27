/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_errors.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 20:20:52 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/27 16:14:04 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/cub3d.h"

char	*ft_to_the_start(char *line, int x, int y)
{
	if (!x)
		while(*(line - 1) == ' ')
			line--;
	if (x)
		while (y--)
			line--;
	return(line);
}

void	my_mlx_pixel_put(t_all *all, int x, int y, int color)
{
	char	*put;

	put = all->win.addr + (y * all->win.line_length + x * (\
	all->win.bits_per_pixel / 8));
	*(unsigned int*)put = color;
}

void	ft_free(char **s)
{
	int i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			free(s[i]);
			i++;
		}
		free(s);
	}
}

void	error_write(int i)
{
	if (i == 0)
		write(1, "Error\ncouldn't create a bmp file\n", 34);
	if (i == 1)
		write(1, "Error\ninvalid screen resolution\n", 32);
	if (i == 2)
		write(1, "Error\ninvalid texture\n", 23);
	if (i == 3)
		write(1, "Error\ninvalid color of floor or ceiling\n", 40);
	if (i == 4)
		write(1, "Error\ninvalid map\n", 18);
	if (i == 5)
		write(1, "Error\nmemory allocation error\n", 30);
	if (i == 6)
		write(1, "Error\nfile should have .cub extension\n", 39);
	if (i == 7)
		write(1, "Error\nnot a valid file\n", 23);
	if (i == 8)
		write(1, "Error\nfile does not exist\n", 26);
	if (i == 9)
		write(1, "Error\ninvalid arguments\n", 24);
	exit(0);
}