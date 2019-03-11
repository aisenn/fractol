/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:44:45 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/13 15:44:48 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_mlx	*init(char *argv)
{
	t_mlx		*mlx;

	if ((mlx = (t_mlx*)malloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->ctrl = (t_ctrl*)malloc(sizeof(t_ctrl))) == NULL)
		return (NULL);
	if ((mlx->mlx = mlx_init()) == NULL)
		return (NULL);
	if ((mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, argv)) == NULL)
		return (NULL);
	if ((mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT)) == NULL)
		return (NULL);
	if ((mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl,
		&mlx->end)) == NULL)
		return (NULL);
	mlx->bpp /= 8;
	mlx->max_iter = 100;
	mlx->palette = get_palette();
	mlx->name = argv;
	set_fractal(mlx);
	mlx->ctrl->key = 0;
	mlx->smooth = 1;
	mlx->n = 2;
	mlx->palette->c = mlx->palette->c - 1;
	return (mlx);
}

static int		check_fractal(char *name)
{
	if (ft_strequ("mandelbrot", name))
		return (0);
	else if (ft_strequ("julia", name))
		return (0);
	else if (ft_strequ("tricorn", name))
		return (0);
	else if (ft_strequ("celtic", name))
		return (0);
	else if (ft_strequ("mandelbrot4", name))
		return (0);
	else if (ft_strequ("cmandelbar", name))
		return (0);
	else if (ft_strequ("pentocorn", name))
		return (0);
	else if (ft_strequ("burningship", name))
		return (0);
	else if (ft_strequ("trijulia", name))
		return (0);
	else if (ft_strequ("necklace", name))
		return (0);
	ft_putstr("\x1b[31mNot correct name: \x1b[1;33m");
	ft_putstr(name);
	ft_putendl("\x1b[49m");
	return (-1);
}

int				fractals_init(int is_menu, char *argv)
{
	t_mlx		*mlx_array;

	if (check_fractal(argv) != -1)
	{
		if (!is_menu)
			information();
		if ((mlx_array = init(argv)) == NULL)
			return (-1);
		mlx_array->menu = is_menu;
		if ((window_split(mlx_array)) == -1)
			return (-1);
	}
	ft_usage(NULL);
	return (-1);
}

/*
**  fork() is leaking, sorry...(
*/

int				fractals_fork(int is_menu, const int argc, char **argv)
{
	t_mlx		**mlx_array;
	int			i;
	pid_t		pid;
	int			ret;

	ret = 0;
	mlx_array = (t_mlx **)malloc(sizeof(t_mlx*) * (argc - 1));
	i = -1;
	while (++i < argc - 1)
	{
		if (check_fractal(argv[i + 1]) != -1)
		{
			ret++;
			pid = fork();
			if (!pid)
			{
				if ((mlx_array[i] = init(argv[i + 1])) == NULL)
					return (-1);
				mlx_array[i]->menu = is_menu;
				if ((window_split(mlx_array[i])) == -1)
					return (-1);
			}
		}
	}
	return (ret);
}

int				menu(t_mlx *mlx)
{
	int			w;
	int			h;

	mlx->mlx = mlx_init();
	if (mlx->check == 0)
	{
		if ((mlx->img = mlx_xpm_file_to_image(mlx->mlx, "src/menu.xpm", &w, &h))
		== NULL)
			return (-1);
		mlx->win = mlx_new_window(mlx->mlx, w, h, "MENU");
	}
	else
	{
		if ((mlx->img = mlx_xpm_file_to_image(mlx->mlx, "src/setting.xpm",
			&w, &h)) == NULL)
			return (-1);
		mlx->win = mlx_new_window(mlx->mlx, w, h, "MENU");
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl, &mlx->end);
	mlx->old_data = (char *)malloc(sizeof(char) * w * h * 4);
	ft_memcpy(mlx->old_data, mlx->data, (size_t)(w * h) * 4);
	menu_hooks(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}

int				main(int argc, char **argv)
{
	t_mlx		mlx;

	if (argc == 1)
		return (ft_usage("argument is missing"));
	else if (ft_strequ(argv[1], "menu"))
	{
		mlx.menu = 1;
		mlx.check = 0;
		mlx.name = "menu";
		if ((menu(&mlx)) == -1)
		{
			ft_putendl("menu.xpm files not found");
			return (-1);
		}
	}
	else if (argc > 2)
	{
		mlx.menu = 0;
		information();
		fractals_fork(mlx.menu, argc, argv);
	}
	else
	{
		mlx.menu = 0;
		fractals_init(mlx.menu, argv[1]);
	}
	return (0);
}
