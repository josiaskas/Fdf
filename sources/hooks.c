/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:47:00 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/07 03:32:56 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/key.h"

static void	ft_change_projection(int key, t_app *app)
{
	if (key == MAIN_PAD_I)
		app->mlx_img->projection = 1;
	else
		app->mlx_img->projection = 0;
	app->mlx_img->alpha = 0;
	app->mlx_img->beta = 0;
	app->mlx_img->gamma = 0;
	ft_draw_fdf(app);
}

static void	ft_move_map(int key, t_app *app)
{
	if (key == ARROW_LEFT)
		app->mlx_img->map_start_x -= 10;
	else if (key == ARROW_RIGHT)
		app->mlx_img->map_start_x += 10;
	else if (key == ARROW_UP)
		app->mlx_img->map_start_y -= 10;
	else
		app->mlx_img->map_start_y += 10;
	ft_draw_fdf(app);
}

int	key_pressed_hook(int key, t_app *app)
{
	if (key == MAIN_PAD_ESC)
		close_window(app);
	else if (key == MAIN_PAD_P || key == MAIN_PAD_I)
		ft_change_projection(key, app);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
		|| key == ARROW_UP || key == ARROW_DOWN)
		ft_move_map(key, app);
	return (0);
}

int	terminate_hook(t_app *app)
{
	if (app->window)
		mlx_destroy_window(app->mlx, app->window);
	return (0);
}

int	close_window(t_app *app)
{
	ft_free_file_stack(app->file_map);
	if (app->map)
		ft_free_map(app->map, app->file_y);
	free(app->mlx_img);
	free(app->title);
	free(app);
	exit(0);
}
