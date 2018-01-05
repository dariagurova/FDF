/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgurova <dariagurova91@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/19 17:44:45 by dgurova           #+#    #+#             */
/*   Updated: 2018/01/03 22:40:14 by dariagurova      ###   ########.fr       */
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

static int		get_height_width(char *filepath, int c)
{
	int		fd;
	int		ret;
	char	*line;

	ret = 0;
	if((fd = open(filepath, O_RDONLY)) < 0)
		error("Error: File open failed");
	if (c == 1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			free(line);
			ret++;
		}
	}
	else
	{
		get_next_line(fd, &line);
		free(line);
		ret = count_words(line);
		while (get_next_line(fd, &line) > 0)
		{
			if (count_words(line) != ret)
				exit_error(1);
				free(line);
		}
	}
	close(fd);
	return (ret);
}

void			parse_args(char *filepath, t_env *env)
{
	int index;

	index = 0;
	env->height = get_height_width(filepath, 1);
	env->width = get_height_width(filepath, 2);
	env->map = (t_point **)malloc(sizeof(t_point *) * env->height);
	while (index < env->height)
	{
		env->map[index] = (t_point *)malloc(sizeof(t_point) * env->width);
		index++;
	}
}

/*static void		smallest_z(t_env *e, int x, int y, int c)
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
}*/
int	valid_read(char *filepath)
{
	int fd;

	if((fd = open(filepath, O_RDONLY)) < 0)
	{
		error("Error: File opening failed");
		exit(0);
	}
	else if (!valid_file(filepath))
	{
		ft_putstr_fd("The extantion of the file is not .fdf\n", 2);
		exit(0);
	}
	return (fd);
}

/*void	free_line(char **line_split, int c)
{
	char **tmp;

	tmp = line_split;
	if (c == 2)
	{
		free(*tmp);
	}

}*/
void			read_file(char *filepath, t_env *env)
{
	//int		fd;
	char	*line;
	char	**line_split;
	char	**temp;
	int		x;
	int		y;

	y = 0;
	if ((env->fd = valid_read(filepath)) > 0)
	//if((fd = open(filepath, O_RDONLY)) < 0)
	//error("Error: File open failed");
	while (get_next_line(env->fd, &line) > 0)
	{
		x = 0;
		if((line_split = ft_strsplit(line, ' ')) != NULL)
		free(line);
		//free_line(line_split, 1);
		temp = line_split;
		while (*line_split != NULL)
		{
			env->map[y][x].z = ft_atoi(*line_split);
			free(*line_split);
			//env->map[y][x].z0 = env->map[y][x].z;
			x++;
			line_split++;
		}
		//free_line(line_split, 2);
		free(temp);
		y++;
	}
	close(env->fd);
}
