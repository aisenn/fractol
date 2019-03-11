/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:44:22 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/13 15:44:25 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <math.h>

void		mandelbrot_iter(t_frac *frac)
{
	double	z_re;
	double	z_im;
	double	zr_tmp;
	int		i;
	double	theta_n;

	z_re = frac->c_re;
	z_im = frac->c_im;
	i = -1;
	while ((++i < frac->max_iter + 2) && (z_re * z_re + z_im * z_im < 4))
	{
		zr_tmp = pow(z_re * z_re + z_im * z_im, frac->n / 2);
		theta_n = atan2(z_im, z_re) * frac->n;
		z_re = zr_tmp * cos(theta_n) + frac->c_re;
		z_im = zr_tmp * sin(theta_n) + frac->c_im;
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}

void		necklace_iter(t_frac *frac)
{
	double	z_re;
	double	z_im;
	double	zr_tmp;
	int		i;

	z_re = frac->c_re;
	z_im = frac->c_im;
	i = -1;
	while ((++i < frac->max_iter + 2) && (z_re * z_re + z_im * z_im < 4))
	{
		z_re = fabs(z_re);
		z_im = fabs(z_im);
		zr_tmp = z_re * z_re + z_im * z_im;
		if (z_re != 0 || z_im != 0)
		{
			z_re = z_re / zr_tmp + frac->jul_re;
			z_im = z_im / zr_tmp + frac->jul_im;
		}
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}

void		julia_iter(t_frac *frac)
{
	double	z_re;
	double	z_im;
	int		i;
	double	zr_tmp;
	double	theta_n;

	z_re = frac->c_re;
	z_im = frac->c_im;
	i = -1;
	while ((++i < frac->max_iter + 2) && (z_re * z_re + z_im * z_im < 4))
	{
		zr_tmp = pow(z_re * z_re + z_im * z_im, frac->n / 2);
		theta_n = atan2(z_im, z_re) * frac->n;
		z_re = zr_tmp * cos(theta_n) + frac->jul_re;
		z_im = zr_tmp * sin(theta_n) + frac->jul_im;
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}

void		tricorn_iter(t_frac *frac)
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
		z_im = z_re * z_im * -2.0 + frac->c_im;
		z_re = zr - zi + frac->c_re;
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}

void		celtic_iter(t_frac *frac)
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
		z_im = z_re * z_im * 2.0 + frac->c_im;
		z_re = fabs(zr - zi) + frac->c_re;
	}
	frac->pix.i = i;
	frac->pix.zn = log(z_re * z_re + z_im * z_im) / 2.0f;
}
