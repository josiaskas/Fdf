/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 22:08:47 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/03 17:31:03 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/color.h"

void	ft_show_error(t_app *app)
{
	if (app->error_code == 2 && !app->error_message)
		app->error_message = "Can't open MAP_FILE";
	else if (app->error_code == 3)
		app->error_message = "Error during MAP Reading";
	else if (app->error_code == 4)
		app->error_message = "Incorrect MAP_FILE";
	else if (app->error_code == 5)
		app->error_message = "MAP: Reading error on a point";
	else if (app->error_code == 7)
		app->error_message = "MLX window init error";
	else if (app->error_code == 8)
		app->error_message = "Usage: ./fdf MAP_FILE";
	ft_print_error(app->error_message, app->error_code);
}

void	ft_print_error(char *error_message, int code)
{
	if (code < 3)
	{
		ft_putstr_fd(SHELL_YELLOW, STDERR_FILENO);
		ft_putstr_fd("FDF: ", STDERR_FILENO);
		if (code == 2)
			ft_putstr_fd("File - ", STDERR_FILENO);
		ft_putstr_fd(error_message, STDERR_FILENO);
		ft_putendl_fd(SHELL_END_COLOR, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd(SHELL_RED, STDERR_FILENO);
		ft_putstr_fd("FDF: ", STDERR_FILENO);
		ft_putstr_fd(error_message, STDERR_FILENO);
		ft_putendl_fd(SHELL_END_COLOR, STDERR_FILENO);
	}
}

void	print_map_file(t_app *app)
{
	int		x;
	int		y;
	int		k;
	t_coord	*datas;

	x = app->file_x;
	y = app->file_y;
	k = app->file_map->length - 1;
	ft_printf("x: %d, y: %d\n", x, y);
	datas = map_stack_to_points(app->file_map, do_nothing);
	while (y)
	{
		x = app->file_x;
		while (x)
		{
			ft_printf("%3d", datas[k].z);
			x--;
			k--;
		}
		write(0, "\n", 1);
		y--;
	}
	free(datas);
}
