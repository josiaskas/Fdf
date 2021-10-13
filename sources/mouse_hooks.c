/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 15:56:42 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/13 16:00:40 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	mouse_pressed(int button, int x, int y, t_app *app)
{
	if (button == 1)
	{
		app->mouse->previous_x = x;
		app->mouse->previous_y = y;
		if (x > 55 && x < 128 && y > 422 && y < 435)
			ft_change_projection(MAIN_PAD_I, app);
		else if (x > 55 && x < 128 && y > 479 && y < 492)
			ft_change_projection(MAIN_PAD_T, app);
		else if (x > 55 && x < 142 && y > 505 && y < 518)
			ft_change_projection(MAIN_PAD_R, app);
		else if (x > 55 && x < 142 && y > 530 && y < 543)
			ft_change_projection(MAIN_PAD_F, app);
		else if (x > MENU_WIDTH && x < W_WIDTH && y > 0 && y < W_HEIGHT)
			app->mouse->b_pressed = true;
	}
	else if (button == MOUSE_SCROLL_DOWN || button == MOUSE_SCROLL_UP)
		ft_zoom_hook(button, app);
	return (0);
}

int	mouse_release(int button, int x, int y, t_app *app)
{
	(void)x;
	(void)y;
	if (button == 1)
		app->mouse->b_pressed = false;
	return (0);
}

int	mouse_moved(int x, int y, t_app *app)
{
	t_mouse	*mouse;
	t_image	*img;

	mouse = app->mouse;
	if (mouse->b_pressed)
	{
		img = app->mlx_img;
		img->map_start_x += (x - mouse->previous_x);
		img->map_start_y += (y - mouse->previous_y);
		mouse->previous_x = x;
		mouse->previous_y = y;
		ft_draw_fdf(app);
	}
	return (0);
}
