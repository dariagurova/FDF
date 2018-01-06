/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:44:09 by dgurova           #+#    #+#             */
/*   Updated: 2018/01/05 22:25:28 by dariagurova      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			smallest(t_env *e, int x, int y, int c)
{
	size_t tmp;

	if (c == 0)
	{
		tmp = ft_abs(e->map[y][x].z);
		if ((!e->smallest && tmp != 0) || (e->smallest > tmp && tmp != 0))
			e->smallest = tmp;
	}
	else
	{
		if (!e->smallest)
			e->smallest = 1;
		while (y < e->height)
		{
			while (x < e->width)
			{
				e->map[y][x].z /= e->smallest;
				e->map[y][x].z0 /= e->smallest;
				x++;
			}
			x = 0;
			y++;
		}
	}
}

void				read_file(char *filepath, t_env *env)
{
	int		x;
	int		y;

	y = 0;
	(env->fd = open(filepath, O_RDONLY)) < 0 ? err(3) : env->fd;
	while (get_next_line(env->fd, &(env->line)) > 0)
	{
		x = 0;
		if ((env->line_split = ft_strsplit(env->line, ' ')) != NULL)
			free(env->line);
		env->temp = env->line_split;
		while (*(env->line_split) != NULL)
		{
			env->map[y][x].z = ft_atoi(*(env->line_split));
			smallest(env, x, y, 0);
			free(*(env->line_split));
			env->map[y][x].z0 = env->map[y][x].z;
			x++;
			env->line_split++;
		}
		free(env->temp);
		y++;
	}
	smallest(env, 0, 0, 1);
}

void				check_args(int ac, char *filepath)
{
	if (ac != 2)
	{
		ft_putstr_fd("You did not pass the right number of arguments.\n", 2);
		ft_putstr_fd("Usage: ./fdf file.fdf\n", 2);
		exit(0);
	}
	if (ft_strstr(filepath, ".fdf") == 0)
	{
		error("Error: File extention is not .fdf.\n", 2);
	}
}

void				err(int c)
{
	if (c == 1)
		ft_putstr_fd("Error: Map is invalid.\n", 2);
	else if (c == 2)
	{
		ft_putstr_fd("Error: mlx failed.\n", 2);
		exit(0);
	}
	else
		ft_putstr_fd("Error: File open() failed.\n", 2);
	exit(0);
}

void				error(char *str, int fd)
{
	ft_putstr_fd(str, fd);
	exit(0);
}
