/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:44:09 by dgurova           #+#    #+#             */
/*   Updated: 2018/01/03 22:40:16 by dariagurova      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	check_args(int ac)
{
	if (ac != 2)
	{
		ft_putstr_fd("You did not pass the right number of arguments.\n", 2);
		ft_putstr_fd("Usage: ./fdf file.fdf\n", 2);
		exit(0);
	}
}

int		valid_file(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (str[len - 1] == 'f' &&
		str[len - 2] == 'd' &&
		str[len - 3] == 'f' &&
		str[len - 4] == '.')
		return (1);
	else
		return (0);
}

void	exit_error(int c)
{
	if (c == 1)
		ft_putstr_fd("Error: Map is invalid.\n", 2);
	if (c == 2)
		ft_putstr_fd("Error: mlx failed.\n", 2);
	exit(0);
}

void	error(char *str)
{
	ft_putendl(str);
	exit(0);
}
