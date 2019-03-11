/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:15:17 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/18 15:15:19 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_usage(char *str)
{
	if (str != NULL)
	{
		ft_putstr("\x1b[4;1;31m");
		ft_putendl(str);
	}
	ft_putendl("\n\x1b[24m\x1b[39mUsage: \x1b[93;1m./fractol \x1b[95m\"menu\"");
	ft_putendl("\x1b[24m\x1b[39m   or: \x1b[93;1m./fractol\x1b[96m \"julia\"");
	ft_putendl("                 \"mandelbrot\"");
	ft_putendl("                 \"tricorn\"");
	ft_putendl("                 \"celtic\"");
	ft_putendl("                 \"mandelbrot4\"");
	ft_putendl("                 \"cmandelbar\"");
	ft_putendl("                 \"pentocorn\"");
	ft_putendl("                 \"burningship\"");
	ft_putendl("                 \"trijulia\"");
	ft_putendl("                 \"necklace\"\x1b[0m");
	return (-1);
}

void	information(void)
{
	ft_putendl("                  --- CONTROLS ---");
	ft_putendl("*******************************************************");
	ft_putendl("*  left click:  center the image under click          *");
	ft_putendl("*  1/2:         select palette                        *");
	ft_putendl("*  w a s d:     move along fractal                    *");
	ft_putendl("*  <^>(arrows): move along fractal                    *");
	ft_putendl("*  scroll:      zoom                                  *");
	ft_putendl("*  space:       activate/deactivate julia iteration   *");
	ft_putendl("*  tab:         smooth/linear coloring                *");
	ft_putendl("*  -/+:         increase/decrease number of iterations*");
	ft_putendl("*  R:           reset                                 *");
	ft_putendl("*  P_UP/P_DOWN: increase/decrease power of fractal    *");
	ft_putendl("*  ESC:         exit                                  *");
	ft_putendl("*******************************************************");
}

void	active(t_mlx *mlx, int x, int y, char c)
{
	int	i;
	int	j;

	if (c == 'A')
	{
		i = x;
		while (i < x + 250)
		{
			j = y;
			while (j < y + 80)
			{
				if ((i == x || j == y || i == x + 249 || j == y + 79) &&
					(i >= 0 && i < 600 && j >= 0 && j < 600))
					*(int *)(mlx->data + ((i * mlx->bpp + j * mlx->sl))) = 0xFF;
				j++;
			}
			i++;
		}
	}
	else
		ft_memcpy(mlx->data, mlx->old_data, M_WIDTH * M_HEIGHT * 4);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
}

void	toggle_info(t_mlx *mlx, int x, int y)
{
	if (x > 558 && y > 550 && x < 600 && y < 600)
	{
		mlx->check = mlx->check == 1 ? 0 : 1;
		destroy_window(mlx);
		menu(mlx);
	}
}
