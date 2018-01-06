/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:44:45 by dgurova           #+#    #+#             */
/*   Updated: 2018/01/05 22:32:45 by dariagurova      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		count_words(const char *line)
{
	int		count;
	int		i;
	int		len;
	char	lastchar;

	i = 0;
	count = 0;
	len = ft_strlen(line);
	if (len > 0)
		lastchar = line[0];
	while (i <= len)
	{
		if ((line[i] == ' ' || line[i] == '\0') && lastchar != ' ')
			count++;
		lastchar = line[i];
		i++;
	}
	return (count);
}

static int		get_height_width(char *filepath, int c, t_env *env)
{
	int		ret;
	char	*line;

	ret = 0;
	(env->fd = open(filepath, O_RDONLY)) < 0 ? error("Open failed.\n", 2) : env->fd;
	if (c == 1) 
		while (get_next_line(env->fd, &line) > 0)
		{
			valid_symbols(line);
			free(line);
			ret++;
		}
	else
	{
		get_next_line(env->fd, &line);
		ret = count_words(line);
		free(line);
		while (get_next_line(env->fd, &line) > 0)
		{
			if (count_words(line) != ret)
				exit_error(1);
				free(line);
		}
	}
	return (ret);
}

void			parse_args(char *filepath, t_env *env)
{
	int index;

	index = 0;
	env->height = get_height_width(filepath, 1, env);
	if ((env->height) == 0)
		error("Error:The file is empty.\n", 2);
	env->width = get_height_width(filepath, 2, env);
	env->map = (t_point **)malloc(sizeof(t_point *) * env->height);
	while (index < env->height)
	{
		env->map[index] = (t_point *)malloc(sizeof(t_point) * env->width);
		index++;
	}
}

void		valid_symbols(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if ((line[i] == '-' && !(ft_isdigit(line[i + 1]))) ||\
			line[i] == '\t')
			error("Error: Found Forbidden Characters.\n", 2);
		i++;
	}
}
