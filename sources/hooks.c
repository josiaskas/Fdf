/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:47:00 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/08 01:12:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/hooks_key.h"

static void	ft_change_projection(int key, t_app *app)
{
	bool	no_rerender;

	no_rerender = false;
	if (key == MAIN_PAD_I)
	{
		if (app->mlx_img->projection == 1)
			no_rerender = true;
		app->mlx_img->projection = 1;
	}
	else if (key == MAIN_PAD_P)
	{
		if (app->mlx_img->projection == 0)
			no_rerender = true;
		app->mlx_img->projection = 0;
	}
	app->mlx_img->alpha = 0;
	app->mlx_img->beta = 0;
	app->mlx_img->gamma = 0;
	app->mlx_img->move_x = 0;
	app->mlx_img->move_y = 0;
	if (!no_rerender)
		ft_draw_fdf(app);
}

int	key_pressed_hook(int key, t_app *app)
{
	if (key == MAIN_PAD_ESC)
		close_window(app);
	else if (key == MAIN_PAD_P || key == MAIN_PAD_I)
		ft_change_projection(key, app);
	else if (key == MAIN_PAD_C)
		ft_change_palete(app);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
		|| key == ARROW_UP || key == ARROW_DOWN)
		ft_move_map(key, app);
	else if (key == NUM_PAD_PLUS || key == MP_PLUS
		|| key == NUM_PAD_MINUS || key == MP_MINUS)
		ft_zoom_hook(key, app);
	else if (key == NUM_PAD_1 || key == MAIN_PAD_1
		|| key == NUM_PAD_2 || key == MAIN_PAD_2
		|| key == NUM_PAD_3 || key == MAIN_PAD_3
		|| key == NUM_PAD_4 || key == MAIN_PAD_4
		|| key == NUM_PAD_6 || key == MAIN_PAD_6
		|| key == NUM_PAD_7 || key == MAIN_PAD_7
		|| key == NUM_PAD_8 || key == MAIN_PAD_8
		|| key == NUM_PAD_9 || key == MAIN_PAD_9)
		ft_rotate_hook(key, app);
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
