/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:46:21 by dgurova           #+#    #+#             */
/*   Updated: 2017/12/19 17:46:24 by dgurova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

int			event_key_next(int keycode, t_env *e)
{
	if (keycode == UNZOOM)
	{
		e->scale.x -= 1;
		e->scale.y += 1;
	}
	if (keycode == ZDOWN)
	{
		e->alt -= 1;
		apply_height(e, -1);
	}
	if (keycode == 12)
		e->color = CW;
	if (keycode == 13)
		e->color = CE;
	if (keycode == 14)
		e->color = CR;
	if (keycode == 15)
		e->color = CT;
	if (keycode == 17)
		e->color = CY;
	if (keycode == 16)
		e->color = CQ;
	ft_draw(e);
	return (1);
}

int			event_key(int keycode, t_env *e)
{
	if (keycode == ESC)
		exit(0);
	if (keycode == RIGHT)
		e->pos.x += 30;
	if (keycode == DOWN)
		e->pos.y += 30;
	if (keycode == LEFT)
		e->pos.x -= 30;
	if (keycode == UP)
		e->pos.y -= 30;
	if (keycode == ZUP)
	{
		e->alt += 1;
		apply_height(e, 1);
	}
	if (keycode == ZOOM)
	{
		e->scale.x += 1;
		e->scale.y -= 1;
	}
	return (event_key_next(keycode, e));
}

int			event_mouse(int button, int x, int y, t_env *e)
{
	if (button == 1 && x && y)
	{
		if (e->color == CQ)
			e->color = CW;
		else if (e->color == CW)
			e->color = CE;
		else if (e->color == CE)
			e->color = CR;
		else if (e->color == CR)
			e->color = CT;
		else if (e->color == CT)
			e->color = CY;
		else
			e->color = CQ;
		ft_draw(e);
	}
	return (1);
	return (1);
}
