/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 00:47:00 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/07 00:48:27 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/key.h"

int	key_pressed_hook(int key, t_app *app)
{
	if (key == MAIN_PAD_ESC)
		terminate_hook(app);
	return (0);
}

int	terminate_hook(t_app *app)
{
	ft_free_file_stack(app->file_map);
	if (app->window)
		mlx_destroy_window(app->mlx, app->window);
	if (app->map)
		ft_free_map(app->map, app->file_y);
	free(app->mlx_img);
	free(app->title);
	free(app);
	exit(0);
}
