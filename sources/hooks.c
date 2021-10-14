/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:47:00 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/14 12:46:59 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/hooks_key.h"

void	ft_change_projection(int key, t_app *app)
{
	if ((key == MAIN_PAD_I) && (app->mlx_img->projection != 1))
	{
		app->mlx_img->projection = 1;
		ft_draw_fdf(app);
	}
	else if ((key == MAIN_PAD_T) && (app->mlx_img->projection != 0))
	{
		app->mlx_img->projection = 0;
		ft_draw_fdf(app);
	}
	else if ((key == MAIN_PAD_R) && (app->mlx_img->projection != 2))
	{
		app->mlx_img->projection = 2;
		ft_draw_fdf(app);
	}
	else if ((key == MAIN_PAD_F) && (app->mlx_img->projection != 3))
	{
		app->mlx_img->projection = 3;
		ft_draw_fdf(app);
	}
	app->mlx_img->alpha = 0;
	app->mlx_img->beta = 0;
	app->mlx_img->gamma = 0;
	app->mlx_img->move_x = 0;
	app->mlx_img->move_y = 0;
}

void	ft_rotate_video_hook(int key, t_app *app)
{
	if ((key == MAIN_PAD_V) && (app->rotate == false))
		app->rotate = true;
	else
		app->rotate = false;
}

int	key_pressed_hook(int key, t_app *app)
{
	if (key == MAIN_PAD_ESC)
		close_window(app);
	else if (key == MAIN_PAD_I || key == MAIN_PAD_T
		|| key == MAIN_PAD_R || key == MAIN_PAD_F)
		ft_change_projection(key, app);
	else if (key == MAIN_PAD_C)
		ft_change_palete(app);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
		|| key == ARROW_UP || key == ARROW_DOWN)
		ft_move_map(key, app);
	else if (key == 69 || key == MP_PLUS || key == 78 || key == MP_MINUS)
		ft_zoom_hook(key, app);
	else if (key == 83 || key == 18 || key == 84 || key == 19
		|| key == NUM_PAD_3 || key == MAIN_PAD_3
		|| key == NUM_PAD_4 || key == MAIN_PAD_4
		|| key == NUM_PAD_6 || key == MAIN_PAD_6
		|| key == NUM_PAD_7 || key == MAIN_PAD_7
		|| key == NUM_PAD_8 || key == MAIN_PAD_8
		|| key == NUM_PAD_9 || key == MAIN_PAD_9)
		ft_rotate_hook(key, app);
	else if (key == MAIN_PAD_U || key == MAIN_PAD_D)
		ft_flat_hook(key, app);
	else if (key == MAIN_PAD_V)
		ft_rotate_video_hook(key, app);
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
