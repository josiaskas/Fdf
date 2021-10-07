#include "../includes/fdf.h"

static bool	check_point_validity(char *nbr, char *color)
{
	size_t	i;

	i = 0;
	if (nbr[i] == '-' || nbr[i] == '+')
		i++;
	while (nbr[i])
	{
		if (!ft_isdigit(nbr[i]))
			return (false);
		i++;
	}
	i = 0;
	if (color != 0)
	{
		if (color[i++] != '0')
			return (false);
		if (color[i] != 'x' && color[i] != 'X')
			return (false);
		while (color[i] && ft_isalnum(color[i]))
			i++;
		if (i < 3 || i > 8)
			return (false);
	}
	return (true);
}

t_coord	*parse_point(char *info[], int x, int y, bool end)
{
	int		i;
	long	z;
	t_coord	*point;

	i = 0;
	z = ft_atol(info[0]);
	if (!check_point_validity(info[0], info[1])
		|| (z > 2147483647 || z < -2147483648))
		return (NULL);
	point = (t_coord *)ft_calloc(1, sizeof(t_coord));
	if (!point)
		return (NULL);
	point->x = x;
	point->y = y;
	point->z = (int)z;
	point->end = end;
	if (info[1])
	{
		point->special = true;
		point->color = ft_atoi_base(info[1], 16);
	}
	return (point);
}

static bool	parse_each_point(char *points[], int len, t_app *app)
{
	int		i;
	char	**data_point;
	t_coord	**line;
	t_coord	*point;

	i = 0;
	data_point = NULL;
	point = NULL;
	line = (t_coord **)ft_calloc(len, sizeof(t_coord *));
	while (points[i] != 0)
	{
		data_point = ft_split(points[i], ',');
		point = parse_point(data_point, i, app->file_y, (i == (len - 1)));
		ft_free_splitted(data_point);
		if (!point)
		{
			app->error_code = 5;
			free_array((void **)line, len);
			return (false);
		}
		line[i] = point;
		i++;
	}
	push(app->file_map, line);
	return (true);
}

static bool	parse_line(char *line, t_app *app)
{
	int			x;
	char		**points;

	app->error_code = 4;
	x = 0;
	points = ft_split(line, ' ');
	if (!points || !points[0])
		return (false);
	while (points[x] != 0)
		x++;
	if (!parse_each_point(points, x, app))
	{
		ft_free_splitted(points);
		return (false);
	}
	ft_free_splitted(points);
	if (x > app->file_x)
		app->file_x = x;
	app->file_y++;
	return (true);
}

bool	read_map_file(t_app *app)
{
	char	*line;
	int		res;

	app->error_code = 3;
	app->file_map = create_stack();
	if (!app->file_map)
		return (false);
	res = get_next_line(app->fd, &line);
	while (res)
	{
		if (!parse_line(line, app))
		{
			close(app->fd);
			free(line);
			return (false);
		}
		free(line);
		res = get_next_line(app->fd, &line);
	}
	if (res == 0)
		free(line);
	close(app->fd);
	if (res < 0)
		return (false);
	return (true);
}
