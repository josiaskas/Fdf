/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 19:50:35 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/04 23:58:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/key.h"

bool	ft_init_image(t_app *app)
{
	t_image	*img;

	app->error_code = 7;
	img = 0;
	app->mlx_img = (t_image *)ft_calloc(1, sizeof(t_image));
	if (!app->mlx_img)
		return (false);
	img = app->mlx_img;
	img->img = mlx_new_image(app->mlx, W_WIDTH, W_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
			&(img->line_length), &(img->endian));
	if (!img->img || !img->addr)
		return (false);
	img->bg_color = BACKGROUND;
	img->menu_bg_color = MENU_BACKGROUND;
	img->palete = 1;
	if (((W_WIDTH - MENU_WIDTH) / app->file_x / 2)
		> (W_HEIGHT / app->file_y / 2))
		img->zoom = W_HEIGHT / app->file_y / 2;
	else
		img->zoom = (W_WIDTH - MENU_WIDTH) / app->file_x / 2;
	img->min = 0;
	img->max = 0;
	return (true);
}

void	draw_background(t_image *img)
{
	unsigned int	*pixel;
	size_t			i;

	i = 0;
	ft_bzero(img->addr, W_WIDTH * W_HEIGHT * (img->bits_per_pixel / 8));
	pixel = (unsigned int *)img->addr;
	while (i < (W_WIDTH * W_HEIGHT))
	{
		if ((i % W_WIDTH) < MENU_WIDTH)
			pixel[i] = (unsigned int)img->menu_bg_color;
		else
			pixel[i] = (unsigned int)img->bg_color;
		i++;
	}
}

bool	draw_menu(t_app *app)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = app->mlx;
	win = app->window;
	mlx_string_put(mlx, win, 65, y += 20, TEXT_COLOR, "How to Use");
	mlx_string_put(mlx, win, 15, y += 35, TEXT_COLOR, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Flatten: </>");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate: Press & Move");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "X-Axis - Key 2 or 8");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Y-Axis - Key 4 or 8");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Z-Axis - Key 1 or 3");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Projection");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "ISO: I Key");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Parallel: P Key");
	return (true);
}

int	key_pressed_hook(int key, t_app *app)
{
	if (key == MAIN_PAD_ESC)
		terminate_hook(app);
	return (0);
}

int	terminate_hook(t_app *app)
{
	free_stack(app->file_map);
	if (app->map)
		free_array((void **)app->map, app->file_y);
	if (app->mlx_img)
		mlx_destroy_image(app->mlx, app->mlx_img->img);
	if (app->window)
		mlx_destroy_window(app->mlx, app->window);
	free(app->mlx_img);
	free(app->title);
	free(app);
	exit(0);
}
