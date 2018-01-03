/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:45:52 by dgurova           #+#    #+#             */
/*   Updated: 2017/12/30 17:05:21 by dgurova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_line(t_env *e, t_coord src, t_coord dst)
{
	t_bresen	ham;

	init_ham(&ham, src, dst);
	while (ham.i <= ham.dx)
	{
		pixel_put(e, src.x, src.y, e->color);
		while (ham.res > 0)
		{
			if (ham.swap)
				src.x += ham.signx;
			else
				src.y += ham.signy;
			ham.res -= 2 * ham.dx;
		}
		if (ham.swap)
			src.y += ham.signy;
		else
			src.x += ham.signx;
		ham.res += 2 * ham.dy;
		ham.i++;
	}
}

void		init_ham(t_bresen *ham, t_coord src, t_coord dst)
{
	int tmp;

	tmp = 0;
	ham->i = 0;
	ham->dx = ft_abs(dst.x - src.x);
	ham->dy = ft_abs(dst.y - src.y);
	ham->signx = (src.x < dst.x ? 1 : -1);
	ham->signy = (src.y < dst.y ? 1 : -1);
	ham->swap = 0;
	ham->res = 2 * ham->dy - ham->dx;
	if (ham->dy > ham->dx)
	{
		tmp = ham->dx;
		ham->dx = ham->dy;
		ham->dy = tmp;
		ham->swap = 1;
	}
}

void		draw_lines(t_env *e, int x, int y)
{
	t_coord p[2];

	p[0].x = e->map[y][x].xp;
	p[0].y = e->map[y][x].yp;
	if (x < e->width - 1)
	{
		p[1].x = e->map[y][x + 1].xp;
		p[1].y = e->map[y][x + 1].yp;
		draw_line(e, p[0], p[1]);
	}
	if (y < e->height - 1)
	{
		p[1].x = e->map[y + 1][x].xp;
		p[1].y = e->map[y + 1][x].yp;
		draw_line(e, p[0], p[1]);
	}
}

void		ft_draw(t_env *e)
{
	int x;
	int y;

	x = 0;
	y = 0;
	apply_proj(e);
	mlx_clear_window(e->mlx, e->win);
	while (y < e->height)
	{
		while (x < e->width)
		{
			draw_lines(e, x, y);
			x++;
		}
		x = 0;
		y++;
	}
}
