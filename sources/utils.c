/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 00:30:13 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/06 23:42:14 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	openfile(char *filename, t_app *app)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		app->error_message = strerror(errno);
		app->error_code = 2;
		return (-1);
	}
	app->file_name = filename;
	return (fd);
}

void	make_title(t_app *app)
{
	char	*title;

	title = "FDF";
	title = ft_strjoin("FDF : ", app->file_name);
	app->title = title;
}

t_coord	***make_map(t_app *app)
{
	int		y;
	t_coord	**line;
	t_coord	***map;

	y = app->file_map->length - 1;
	map = (t_coord ***)ft_calloc(app->file_y, sizeof(t_coord **));
	while (app->file_map->length)
	{
		line = (t_coord **)pop(app->file_map);
		map[y] = line;
		y--;
	}
	return (map);
}

void	ft_free_map(t_coord	***map, size_t nb_lines)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < nb_lines)
	{
		x = 0;
		while (map[y][x]->end == false)
			x++;
		free_array((void **)map[y], x + 1);
		y++;
	}
	free(map);
}

void	ft_free_file_stack(t_stack *file_map)
{
	size_t	x;
	t_coord	**line;

	x = 0;
	while (file_map->length)
	{
		line = (t_coord **)pop(file_map);
		x = 0;
		while (line[x]->end == false)
		{
			free(line[x]);
			x++;
		}
		free(line[x]);
		free(line);
	}
	free_stack(file_map);
}
