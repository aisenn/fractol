/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:44:54 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/13 15:44:56 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			set_fractal(t_mlx *mlx)
{
	mlx->jul_re = -0.70176;
	mlx->jul_im = -0.3842;
	mlx->re_min = -2.0;
	mlx->re_max = 2.0;
	mlx->im_min = 2.0;
	mlx->im_max = -2.0;
	if (ft_strequ(mlx->name, "burningship") || ft_strequ(mlx->name, "celtic") ||
	ft_strequ(mlx->name, "cmandelbar") || ft_strequ(mlx->name, "mandelbrot"))
	{
		mlx->re_min = -2.5;
		mlx->re_max = 1.5;
		mlx->im_min = 2.0;
		mlx->im_max = -2.0;
	}
	if (ft_strequ(mlx->name, "celtic"))
	{
		mlx->re_min = -3.0;
		mlx->re_max = 1.0;
	}
	if (ft_strequ(mlx->name, "burningship"))
	{
		mlx->im_min = 1.6;
		mlx->im_max = -2.4;
	}
	ft_bzero(mlx->data, WIDTH * HEIGHT * 4);
}

static double	interpolate(double start, double end, double interpolation)
{
	return (start + ((end - start) * interpolation));
}

static void		apply_zoom(t_mlx *mlx, double m_re, double m_im, double zoom)
{
	double		interpolation;

	if (zoom == 1)
		interpolation = 0.92;
	else
		interpolation = 1.03;
	mlx->re_min = interpolate(m_re, mlx->re_min, interpolation);
	mlx->re_max = interpolate(m_re, mlx->re_max, interpolation);
	mlx->im_min = interpolate(m_im, mlx->im_min, interpolation);
	mlx->im_max = interpolate(m_im, mlx->im_max, interpolation);
}

int				hook_mouseon(int click, int x, int y, t_mlx *mlx)
{
	double		a;
	double		b;
	double		m_re;
	double		m_im;

	a = mlx->re_max - mlx->re_min;
	b = mlx->im_max - mlx->im_min;
	m_re = (mlx->re_min + x * a / (WIDTH - 1));
	m_im = (mlx->im_max - y * b / (HEIGHT - 1));
	if (click == 1 && !mlx->ctrl->key)
	{
		a /= 2;
		b /= 2;
		mlx->re_min = m_re + -a;
		mlx->re_max = m_re + a;
		mlx->im_min = m_im - b;
		mlx->im_max = m_im - -b;
		ft_bzero(mlx->data, WIDTH * HEIGHT * 4);
	}
	if (click == 5)
		apply_zoom(mlx, m_re, m_im, 1);
	else if (click == 4)
		apply_zoom(mlx, m_re, m_im, -1);
	window_split(mlx);
	return (0);
}

int				hook_mouse_move(int x, int y, t_mlx *mlx)
{
	double		a;
	double		b;
	double		m_re;
	double		m_im;

	if (mlx->ctrl->key)
	{
		a = mlx->re_max - mlx->re_min;
		b = mlx->im_max - mlx->im_min;
		m_re = (mlx->re_min + x * a / (WIDTH - 1));
		m_im = (mlx->im_max - y * b / (HEIGHT - 1));
		mlx->jul_re = m_re;
		mlx->jul_im = m_im;
	}
	if (mlx->ctrl->key)
		window_split(mlx);
	return (0);
}
