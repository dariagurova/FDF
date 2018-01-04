/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/14 14:57:16 by dgurova           #+#    #+#             */
/*   Updated: 2017/12/22 15:18:04 by dgurova          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "minilibx_macos/includes/mlx.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>

# define PI 3.141592653589793
# define RAD(x) (x * PI / 180)
# define WIN_WIDTH 1200
# define WIN_HEIGHT 1200
# define CQ 0xFFFFFF
# define CW 0xcd6600
# define CE  0xced1
# define CR 0xffff00
# define CT 0xa020f0
# define CY 0xcd3278

# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124
# define ESC 53
# define ZOOM 69
# define UNZOOM 78
# define ZUP 32
# define ZDOWN 2

typedef struct			s_point
{
	int					z;
	int					z0;
	int					xp;
	int					yp;
}						t_point;

typedef struct			s_coord
{
	int					x;
	int					y;
}						t_coord;

typedef struct			s_env
{
	void				*mlx;
	void				*win;
	t_point				**map;
	t_coord				scale;
	t_coord				pos;
	int					height;
	int					width;
	int					alt;
	size_t				smallest;
	int					color;
}						t_env;

typedef struct			s_bresen
{
	int					i;
	int					dx;
	int					dy;
	int					signx;
	int					signy;
	int					swap;
	int					res;
}						t_bresen;

void					init_ham(t_bresen *ham, t_coord src, t_coord dst);
void					check_args(int ac);
int						valid_file(char *str);
void					parse_args(char *filepath, t_env *env);
void					read_file(char *filepath, t_env *env);
void					exit_error(int c);
void					apply_proj(t_env *env);
void					apply_height(t_env *e, int c);
void					draw_lines(t_env *env, int x, int y);
void					pixel_put(t_env *e, int x, int y, int color);
void					ft_draw(t_env *e);
int						event_mouse(int button, int x, int y, t_env *env);
int						event_key(int keycode, t_env *env);
int						event_key_next(int keycode, t_env *e);
void					error(char *str);
#endif
