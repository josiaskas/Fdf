/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_suite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 20:58:09 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/13 00:39:12 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/hooks_key.h"

void	ft_move_map(int key, t_app *app)
{
	if (key == ARROW_LEFT)
		app->mlx_img->move_x -= 10;
	else if (key == ARROW_RIGHT)
		app->mlx_img->move_x += 10;
	else if (key == ARROW_UP)
		app->mlx_img->move_y -= 10;
	else
		app->mlx_img->move_y += 10;
	ft_draw_fdf(app);
}

void	ft_change_palete(t_app *app)
{
	int	current_p;

	current_p = app->mlx_img->palette;
	current_p += 1;
	current_p = current_p % 6;
	if (current_p == 0)
		current_p = 1;
	app->mlx_img->palette = current_p;
	ft_draw_fdf(app);
}

void	ft_zoom_hook(int key, t_app *app)
{
	int	big_x;
	int	big_y;

	big_x = W_WIDTH - MENU_WIDTH;
	big_y = W_HEIGHT;
	if ((key == NUM_PAD_PLUS) || (key == MP_PLUS) || (key == 4))
		app->mlx_img->zoom++;
	else if ((key == NUM_PAD_MINUS) || (key == MP_MINUS) || (key == 5))
		app->mlx_img->zoom--;
	if (app->mlx_img->zoom < 1)
	{
		if ((big_x / app->file_x / 2) > (big_y / app->file_y / 2))
			app->mlx_img->zoom = big_y / app->file_y / 2;
		else
			app->mlx_img->zoom = big_x / app->file_x / 2;
	}
	if (app->mlx_img->zoom < 1)
		app->mlx_img->zoom = 1;
	ft_draw_fdf(app);
}

void	ft_flat_hook(int key, t_app *app)
{
	if (key == MAIN_PAD_U)
		app->mlx_img->z_zoom += 0.1;
	else if (key == MAIN_PAD_D)
		app->mlx_img->z_zoom -= 0.1;
	if (app->mlx_img->z_zoom < 0.1)
		return ;
	else if (app->mlx_img->z_zoom > 2)
		return ;
	else
		ft_draw_fdf(app);
}

void	ft_rotate_hook(int key, t_app *app)
{
	t_image	*img;

	img = app->mlx_img;
	if (key == NUM_PAD_4 || key == MAIN_PAD_4)
		img->alpha += 0.05;
	else if (key == NUM_PAD_6 || key == MAIN_PAD_6)
		img->alpha -= 0.05;
	else if (key == NUM_PAD_2 || key == MAIN_PAD_2)
		img->beta += 0.05;
	else if (key == NUM_PAD_8 || key == MAIN_PAD_8)
		img->beta -= 0.05;
	else if (key == NUM_PAD_1 || key == MAIN_PAD_1)
		img->gamma += 0.05;
	else if (key == NUM_PAD_9 || key == MAIN_PAD_9)
		img->gamma -= 0.05;
	ft_draw_fdf(app);
}
