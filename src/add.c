/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:27:29 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/18 15:27:32 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	hook_click(int click, int x, int y, t_mlx *mlx)
{
	if (click == 1)
	{
		if (x > 37 && y > 99 && x < 287 && y < 179)
			fractals_init(mlx->menu, "julia");
		else if (x > 37 && y > 199 && x < 287 && y < 279)
			fractals_init(mlx->menu, "mandelbrot");
		else if (x > 37 && y > 299 && x < 287 && y < 379)
			fractals_init(mlx->menu, "tricorn");
		else if (x > 37 && y > 399 && x < 287 && y < 479)
			fractals_init(mlx->menu, "celtic");
		else if (x > 37 && y > 499 && x < 287 && y < 579)
			fractals_init(mlx->menu, "mandelbrot4");
		else if (x > 307 && y > 99 && x < 557 && y < 179)
			fractals_init(mlx->menu, "cmandelbar");
		else if (x > 307 && y > 199 && x < 557 && y < 279)
			fractals_init(mlx->menu, "pentocorn");
		else if (x > 307 && y > 299 && x < 557 && y < 379)
			fractals_init(mlx->menu, "burningship");
		else if (x > 307 && y > 399 && x < 557 && y < 479)
			fractals_init(mlx->menu, "trijulia");
		else if (x > 307 && y > 499 && x < 557 && y < 579)
			fractals_init(mlx->menu, "necklace");
		toggle_info(mlx, x, y);
	}
	return (0);
}

static int	hook_menu_move(int x, int y, t_mlx *mlx)
{
	if (x > 37 && y > 99 && x < 287 && y < 179)
		active(mlx, 37, 99, 'A');
	else if (x > 37 && y > 199 && x < 287 && y < 279)
		active(mlx, 37, 199, 'A');
	else if (x > 37 && y > 299 && x < 287 && y < 379)
		active(mlx, 37, 299, 'A');
	else if (x > 37 && y > 399 && x < 287 && y < 479)
		active(mlx, 37, 399, 'A');
	else if (x > 37 && y > 499 && x < 287 && y < 579)
		active(mlx, 37, 499, 'A');
	else if (x > 307 && y > 99 && x < 557 && y < 179)
		active(mlx, 307, 99, 'A');
	else if (x > 307 && y > 199 && x < 557 && y < 279)
		active(mlx, 307, 199, 'A');
	else if (x > 307 && y > 299 && x < 557 && y < 379)
		active(mlx, 307, 299, 'A');
	else if (x > 307 && y > 399 && x < 557 && y < 479)
		active(mlx, 307, 399, 'A');
	else if (x > 307 && y > 499 && x < 557 && y < 579)
		active(mlx, 307, 499, 'A');
	else if (x > 558 && y > 550 && x < 600 && y < 600)
		active(mlx, 558, 560, 'A');
	else
		active(mlx, 0, 0, 'R');
	return (0);
}

static int	hook_menu_keyon(int key)
{
	if (key == KEY_ESC)
		exit(EXIT_SUCCESS);
	return (0);
}

static int	close_menu(void *close)
{
	if (close != NULL)
		exit(EXIT_SUCCESS);
	return (0);
}

void		menu_hooks(t_mlx *mlx)
{
	mlx->data = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->sl, &mlx->end);
	mlx->bpp /= 8;
	mlx_hook(mlx->win, 6, 0, hook_menu_move, mlx);
	mlx_hook(mlx->win, 4, 0, hook_click, mlx);
	mlx_hook(mlx->win, 2, 0, hook_menu_keyon, mlx);
	mlx_hook(mlx->win, 17, 0, close_menu, mlx);
}
