/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:43:38 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/13 15:43:41 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "math.h"

t_palette		*get_palette(void)
{
	static		t_palette	a[11];

	a[0] = (t_palette){5, {0x96ceb4, 0xffcc5c, 0xff6f69, 0xced07d, 0x0e9aa7},
			&a[1], &a[9]};
	a[1] = (t_palette){5, {0x0D1C33, 0x17373C, 0x2B6832, 0x4F9300, 0xA1D700},
			&a[2], &a[0]};
	a[2] = (t_palette){5, {0x002F2F, 0x046380, 0xEFECCA, 0xA7A37E, 0xE6E2AF},
			&a[3], &a[1]};
	a[3] = (t_palette){7, {0x1d00ff, 0xfffc00, 0x342e2e, 0xffffff, 0x57470d},
			&a[4], &a[2]};
	a[4] = (t_palette){5, {0xD94A39, 0x403231, 0x8C5AA6, 0x8BB16C, 0xD9C860},
			&a[5], &a[3]};
	a[5] = (t_palette){5, {0x78EDF2, 0x337073, 0xA65A8B, 0x7AF2B5, 0x337352},
			&a[6], &a[4]};
	a[6] = (t_palette){5, {0x88B4E3, 0xD4EBFB, 0xF1EABE, 0xF6CB5A, 0xFFAA00},
			&a[7], &a[5]};
	a[7] = (t_palette){5, {0x000000, 0xffff, 0x6C7A7D, 0x00002F, 0xffff},
			&a[8], &a[6]};
	a[8] = (t_palette){5, {0x920031, 0x00042b, 0x3c0c00, 0x470053, 0xeb0000},
			&a[9], &a[7]};
	a[9] = (t_palette){6, {0x000000, 0xff66ab, 0x8090c7, 0xd8d8d8, 0x333333,
			0x000000}, &a[0], &a[8]};
	a[10] = (t_palette){5, {0x00df8b, 0x1d88d8, 0xd409cc, 0xf21e5e, 0xe7df1b},
			&a[1], &a[9]};
	return (&a[0]);
}

static int		linear_color(double i, t_palette *p)
{
	double		t;
	t_col		c;
	int			c1;
	int			c2;
	int			rgb;

	t = 1 - (fmod(i, 1.0f / p->c) * p->c);
	c1 = p->colors[(int)(i * p->c) + 1];
	c2 = p->colors[(int)(i * p->c)];
	c.r = ft_lerp(c1 >> 16, c2 >> 16, t);
	c.g = ft_lerp((c1 >> 8) & 255, (c2 >> 8) & 255, t);
	c.b = ft_lerp(c1 & 255, c2 & 255, t);
	rgb = (((int)c.r & 0x0ff) << 16) |
			(((int)c.g & 0x0ff) << 8) |
			((int)c.b & 0x0ff);
	return (rgb);
}

static int		smooth_color(t_pix *p, int max, t_palette *pal)
{
	double		i;
	double		nu;

	nu = log(p->zn);
	i = p->i + 1 - nu;
	if (i < 0)
		i = 0;
	return (linear_color(i / max, pal));
}

int				get_color(t_mlx *mlx, t_pix *pix)
{
	if (pix->i >= mlx->max_iter)
		return (0x000000);
	if (mlx->smooth)
		return (smooth_color(pix, mlx->max_iter, mlx->palette));
	return (linear_color((double)pix->i / mlx->max_iter, mlx->palette));
}
