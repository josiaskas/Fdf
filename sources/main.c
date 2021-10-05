#include "../includes/fdf.h"

static void	loop_app(t_app *app)
{
	t_image	*img;

	img = app->mlx_img;
	ft_draw_fdf(app);
	mlx_hook(app->window, 2, 0, key_pressed_hook, app);
	//mlx_hook(app->window, 17, 0, terminate_hook, app);
	mlx_loop(app->mlx);
}

static bool	init_app(t_app *app, int fd)
{
	app->fd = fd;
	app->mlx = mlx_init();
	if (!app->mlx)
	{
		app->error_code = 3;
		return (false);
	}
	make_title(app);
	if (!read_map_file(app))
		return (false);
	app->map = make_map(app);
	app->window = mlx_new_window(app->mlx, W_WIDTH, W_HEIGHT, app->title);
	if (!app->window || !ft_init_image(app))
	{
		app->error_code = 7;
		return (false);
	}
	return (true);
}

static int	close_app(t_app *app, bool	with_errors, bool all)
{
	if (with_errors)
		ft_show_error(app);
	if (all)
	{
		free_stack(app->file_map);
		if (app->window)
			mlx_destroy_window(app->mlx, app->window);
		if (app->map)
			free_array((void **)app->map, app->file_y);
		free(app->mlx_img);
		free(app->title);
	}
	free(app);
	if (with_errors)
		return (1);
	else
		return (0);
}

int	main(int argc, char *argv[])
{
	t_app	*app;
	int		fd;

	app = NULL;
	if (argc == 2)
	{
		app = (t_app *)ft_calloc(1, sizeof(t_app));
		fd = openfile(argv[1], app);
		if (fd < 0)
			return (close_app(app, true, false));
		else
		{
			if (init_app(app, fd))
			{
				loop_app(app);
				return (close_app(app, false, true));
			}
			else
				return (close_app(app, true, true));
		}
	}
	ft_print_error("Usage: ./fdf MAP_FILE", 1);
	return (1);
}
