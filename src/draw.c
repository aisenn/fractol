/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:44:08 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/13 15:44:11 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		set_pixel(t_mlx *mlx, int x, int y, int colour)
{
	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
		*(int *)(mlx->data + ((x * mlx->bpp + y * mlx->sl))) = colour;
}

static void		*thread_func(void *mlx)
{
	int			x;
	int			y;
	t_th		*th;

	th = (t_th*)mlx;
	y = 0;
	while (y < HEIGHT)
	{
		x = WIDTH * th->i / AMOUNT_OF_THREADS;
		th->frac->c_im = th->mlx->im_max - y *
			(th->mlx->im_max - th->mlx->im_min) / (HEIGHT - 1);
		while (x < WIDTH * (th->i + 1) / AMOUNT_OF_THREADS)
		{
			th->frac->c_re = th->mlx->re_min + x *
				-(th->mlx->im_max - th->mlx->im_min) / (WIDTH - 1);
			th->frac->iter_fn(th->frac);
			set_pixel(th->mlx, x, y, get_color(th->mlx, &th->frac->pix));
			x++;
		}
		y++;
	}
	return (NULL);
}

static void		choose_fractal(t_frac *frac, char *name)
{
	if (ft_strequ("mandelbrot", name))
		frac->iter_fn = mandelbrot_iter;
	else if (ft_strequ("julia", name))
		frac->iter_fn = julia_iter;
	else if (ft_strequ("tricorn", name))
		frac->iter_fn = tricorn_iter;
	else if (ft_strequ("celtic", name))
		frac->iter_fn = celtic_iter;
	else if (ft_strequ("mandelbrot4", name))
		frac->iter_fn = mandelbrot4_iter;
	else if (ft_strequ("cmandelbar", name))
		frac->iter_fn = cmandelbar_iter;
	else if (ft_strequ("pentocorn", name))
		frac->iter_fn = pentocorn_iter;
	else if (ft_strequ("burningship", name))
		frac->iter_fn = burningship_iter;
	else if (ft_strequ("trijulia", name))
		frac->iter_fn = trijulia_iter;
	if (ft_strequ("necklace", name))
		frac->iter_fn = necklace_iter;
}

static t_frac	*ft_copy(t_mlx *mlx)
{
	t_frac		*frac;

	if ((frac = (t_frac*)malloc(sizeof(t_frac))) == NULL)
		return (NULL);
	frac->c_im = 0;
	frac->c_re = 0;
	frac->jul_im = mlx->jul_im;
	frac->jul_re = mlx->jul_re;
	frac->max_iter = mlx->max_iter;
	frac->z_im = 0;
	frac->z_re = 0;
	frac->n = mlx->n;
	choose_fractal(frac, mlx->name);
	return (frac);
}

int				window_split(t_mlx *mlx)
{
	pthread_t	threads[AMOUNT_OF_THREADS];
	t_th		th[AMOUNT_OF_THREADS];
	int			i;

	i = -1;
	while (++i < AMOUNT_OF_THREADS)
	{
		th[i].mlx = mlx;
		th[i].i = i;
		if ((th[i].frac = ft_copy(mlx)) == NULL)
			return (-1);
		pthread_create(&threads[i], NULL, thread_func, &th[i]);
	}
	i = -1;
	while (++i < AMOUNT_OF_THREADS)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	hooks(mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
