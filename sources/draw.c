/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 02:25:00 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/07 01:50:46 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_coord	prepare_point(t_coord *original, t_app *app)
{
	t_coord	result;
	bool	percent;
	t_image	*img;

	img = app->mlx_img;
	percent = ft_percent(img->min, img->max, original->z);
	result.x = original->x * img->zoom;
	result.y = original->y * img->zoom;
	result.z = original->z * img->zoom;
	result.special = original->special;
	if (result.special)
		result.color = original->color;
	else
		result.color = ft_get_palete_color(img->palete, percent);
	result.x += img->map_start_x;
	result.y += img->map_start_y;
	return (result);
}

void	draw_map(t_app *app, t_coord ***map)
{
	int		x;
	int		y;
	bool	smaller_line;

	y = 0;
	x = 0;
	while (y < app->file_y)
	{
		x = 0;
		smaller_line = false;
		while (map[y][x]->end == false)
		{
			draw_segment(prepare_point(map[y][x], app),
				prepare_point(map[y][x + 1], app), app->mlx_img);
			if ((y != (app->file_y - 1)) && !smaller_line)
			{
				smaller_line = map[y + 1][x]->end;
				draw_segment(prepare_point(map[y][x], app),
					prepare_point(map[y + 1][x], app), app->mlx_img);
			}
			x++;
		}
		if ((y != (app->file_y - 1)) && !smaller_line)
			draw_segment(prepare_point(map[y][x], app),
				prepare_point(map[y + 1][x], app), app->mlx_img);
		y++;
	}
	mlx_put_image_to_window(app->mlx, app->window, app->mlx_img->img, 0, 0);
}

void	ft_project(t_app *app, t_image *img)
{
	int		x;
	int		y;

	y = 0;
	x = 0;
	while (y < app->file_y)
	{
		x = 0;
		while (app->map[y][x]->end == false)
		{
			ft_rotation_matrix(app->map[y][x], img);
			project_choice(app->map[y][x], img);
			x++;
		}
		y++;
	}
}

void	ft_draw_fdf(t_app *app)
{
	draw_background(app->mlx_img);
	ft_project(app, app->mlx_img);
	draw_map(app, app->map);
	draw_menu(app);
}
