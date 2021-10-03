/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 00:30:13 by jkasongo          #+#    #+#             */
/*   Updated: 2021/09/28 21:14:41 by jkasongo         ###   ########.fr       */
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

t_coord	do_nothing(void *point)
{
	t_coord	*data;
	t_coord	result;

	data = (t_coord *)point;
	result.x = data->x;
	result.y = data->y;
	result.z = data->z;
	result.color = data->color;
	result.special = data->special;
	return (result);
}

void	make_title(t_app *app)
{
	char	*title;

	title = "FDF";
	title = ft_strjoin("FDF : ", app->file_name);
	app->title = title;
}

void	ft_rotate_map_stack(t_app *app)
{
	int	k;

	k = 0;
	k = app->file_map->length - 1;
	while (k--)
		rotate(app->file_map);
}

t_coord	*map_stack_to_points(t_stack *stack, t_coord (*apply)(void *))
{
	t_coord			*results;
	t_stack_node	*node;
	int				i;

	i = 0;
	if (!stack)
		return (0);
	if (!stack->length)
		return (0);
	results = (t_coord *)malloc(sizeof(t_coord) * (stack->length));
	if (!results)
		return (0);
	node = stack->head;
	while (i < stack->length)
	{
		results[i] = apply(node->content);
		node = node->next;
		i++;
	}
	return (results);
}
