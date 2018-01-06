/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:43:28 by dgurova           #+#    #+#             */
/*   Updated: 2018/01/05 20:00:19 by dariagurova      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void			init_env(t_env *e)
{
	if ((e->mlx = mlx_init()) == (void *)0)
		exit_error(2);
	e->scale.x = 30;
	e->scale.y = -30;
	e->pos.x = 500;
	e->pos.y = 500;
	e->alt = 1;
	e->color = CQ;
}

static void			adjust_scale(t_env *e)
{
	while (e->scale.x * e->width > WIN_WIDTH && e->scale.x > 0)
		e->scale.x -= 1;
	while (e->scale.y * e->height < -WIN_HEIGHT && e->scale.y < 0)
		e->scale.y += 1;
	if (ft_abs(e->scale.x) < ft_abs(e->scale.y))
		e->scale.y = -(e->scale.x);
	else
		e->scale.x = -(e->scale.y);
}

void				pixel_put(t_env *e, int x, int y, int color)
{
	mlx_pixel_put(e->mlx, e->win, e->pos.x + x, e->pos.y + y, color);
}

void free_map(t_point **map, int height)
{
	int i;

	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void free_env(t_env *env)
{
	free_map(env->map, env->height);
	mlx_destroy_window(env->mlx, env->win);
	free(env->mlx);
	free(env);
}

int					main(int ac, char **av)
{
	t_env *env;

	env = (t_env *)malloc(sizeof(t_env));
	if (env == NULL)
		return (1);
	check_args(ac, av[1]);
	init_env(env);
	parse_args(av[1], env);
	read_file(av[1], env);
	adjust_scale(env);
	env->win = mlx_new_window(env->mlx, WIN_WIDTH, WIN_HEIGHT, "test");
	if (env->win == (void *)0)
		exit_error(2);
	ft_draw(env);
	mlx_key_hook(env->win, event_key, env);
	mlx_mouse_hook(env->win, event_mouse, env);
	mlx_loop(env->mlx);
}
