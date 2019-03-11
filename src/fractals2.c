/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:44:31 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/13 15:44:37 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void		mandelbrot4_iter(t_frac *frac)
{
	double	z_re;
	double	z_im;
	double	zr;
	double	zi;
	int		i;

	z_re = frac->c_re;
	z_im = frac->c_im;
	i = -1;
	while ((++i < frac->max_iter + 2) && (z_re * z_re + z_im * z_im < 4))
	{
		zr = z_re * z_re;
		zi = z_im * z_im;
		z_im = 4 * z_re * z_im * (zr - zi) + frac->c_im;
		z_re = zr * zr + zi * zi - 6 * zr * zi + frac->c_re;
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}

void		cmandelbar_iter(t_frac *frac)
{
	double	z_re;
	double	z_im;
	double	zr;
	double	zi;
	int		i;

	z_re = frac->c_re;
	z_im = frac->c_im;
	i = -1;
	while ((++i < frac->max_iter + 2) && (z_re * z_re + z_im * z_im < 4))
	{
		zr = z_re * z_re;
		zi = z_im * z_im;
		z_im = (z_re * z_im * -2.0 + frac->c_im);
		z_re = (fabs(zr - zi) + frac->c_re);
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}

void		pentocorn_iter(t_frac *frac)
{
	double	z_re;
	double	z_im;
	double	zr;
	double	zi;
	int		i;

	z_re = frac->c_re;
	z_im = frac->c_im;
	i = -1;
	while ((++i < frac->max_iter + 2) && (z_re * z_re + z_im * z_im < 4))
	{
		zr = z_re * z_re;
		zi = z_im * z_im;
		z_im = -4 * z_re * z_im * (zr - zi) + frac->c_im;
		z_re = zr * zr + zi * zi - 6 * zr * zi + frac->c_re;
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}

void		burningship_iter(t_frac *frac)
{
	double	z_re;
	double	z_im;
	double	zr;
	double	zi;
	int		i;

	z_re = frac->c_re;
	z_im = frac->c_im;
	i = -1;
	while ((++i < frac->max_iter + 2) && (z_re * z_re + z_im * z_im < 4))
	{
		zr = z_re * z_re;
		zi = z_im * z_im;
		z_im = fabs(z_re * z_im) * 2.0 + frac->c_im;
		z_re = zr - zi + frac->c_re;
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}

void		trijulia_iter(t_frac *frac)
{
	double	z_re;
	double	z_im;
	double	zr;
	double	zi;
	int		i;

	z_re = frac->c_re;
	z_im = frac->c_im;
	i = -1;
	while ((++i < frac->max_iter) && (z_re * z_re + z_im * z_im < 4))
	{
		zr = z_re * z_re;
		zi = z_im * z_im;
		z_re = z_re * (zr - 3 * zi) + frac->jul_re;
		z_im = z_im * (3 * zr - zi) + frac->jul_im;
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}
