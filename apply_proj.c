/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_proj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:45:22 by dgurova           #+#    #+#             */
/*   Updated: 2018/01/02 15:51:02 by dgurova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	proj_x(int x, int y, t_env *e)
{
	double ret;



	ret = (x * cos(RAD(44))) - y * sin(RAD(21));
	ret = ret * e->scale.x;
	return ((int)ret);
}

static int	proj_y(int x, int y, t_env *e)
{
	double ret;

	ret = 


	/*x * sin(RAD(42)) * sin(RAD(21)) +
				y * sin(RAD(21)) * cos(RAD(42)) +
				e->map[y][x].z * cos(RAD(21));*/

	(x * sin(RAD(21)) * sin(RAD(42)) +
				y * sin(RAD(21)) * cos(RAD(42)) +
				e->map[y][x].z * cos(RAD(21)));


	/*x * sin(RAD(21)) * cos(RAD(42)) +
				y * cos(RAD(21)) * cos(RAD(42)) -
				e->map[y][x].z * sin(RAD(21));*/
	ret = ret * e->scale.y;
	return ((int)ret);
}

void		apply_height(t_env *e, int c)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < e->height)
	{
		while (x < e->width)
		{
			if (e->map[y][x].z0 != 0)
			{
				if (c == 1)
					e->map[y][x].z = (e->map[y][x].z0 * e->alt);
				else
					e->map[y][x].z = (e->map[y][x].z0 * e->alt);
				e->map[y][x].xp = proj_x(x, y, e);
				e->map[y][x].yp = proj_y(x, y, e);
			}
			x++;
		}
		x = 0;
		y++;
	}
}

void		apply_proj(t_env *e)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < e->height)
	{
		while (x < e->width)
		{
			e->map[y][x].xp = proj_x(x, y, e);
			e->map[y][x].yp = proj_y(x, y, e);
			x++;
		}
		x = 0;
		y++;
	}
}
