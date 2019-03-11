/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 15:43:54 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/13 15:43:57 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		destroy_window(t_mlx *mlx)
{
	if (mlx->menu == 1)
	{
		mlx_destroy_image(mlx->mlx, mlx->img);
		mlx_destroy_window(mlx->mlx, mlx->win);
	}
	else
		exit(EXIT_SUCCESS);
}

static void	move(int key, t_mlx *mlx)
{
	double	w;
	double	h;

	w = (mlx->re_max - mlx->re_min) * 0.05f;
	h = (mlx->im_max - mlx->im_min) * 0.05f;
	if (key == KEY_UP || key == KEY_W)
	{
		mlx->im_max += h;
		mlx->im_min += h;
	}
	else if (key == KEY_DOWN || key == KEY_S)
	{
		mlx->im_max -= h;
		mlx->im_min -= h;
	}
	else if (key == KEY_LEFT || key == KEY_A)
	{
		mlx->re_min -= w;
		mlx->re_max -= w;
	}
	else if (key == KEY_RIGHT || key == KEY_D)
	{
		mlx->re_max += w;
		mlx->re_min += w;
	}
}

static int	hook_keyon(int key, t_mlx *mlx)
{
	if (key == KEY_R)
		set_fractal(mlx);
	else if (key == 18)
		mlx->palette = mlx->palette->next;
	else if (key == 19)
		mlx->palette = mlx->palette->previous;
	else if (key == KEY_TAB)
		mlx->smooth = mlx->smooth == 1 ? 0 : 1;
	else if (key == KEY_PLUS || key == NUM_PLUS)
		mlx->max_iter++;
	else if (key == KEY_MINUS || key == NUM_MINUS)
		mlx->max_iter--;
	else if (key == KEY_SPACE)
		mlx->ctrl->key = !mlx->ctrl->key;
	else if (key == PAGE_UP)
		mlx->n = (mlx->n < -3 || mlx->n > 1) ? mlx->n + 1 : 2;
	else if (key == PAGE_DOWN)
		mlx->n = (mlx->n > 3 || mlx->n < -1) ? mlx->n - 1 : -2;
	move(key, mlx);
	if (key == KEY_ESC)
		destroy_window(mlx);
	else
		window_split(mlx);
	return (0);
}

static int	close_button(t_mlx *mlx)
{
	if (mlx != NULL)
	{
		if (mlx->menu == 1)
			return (1);
		else
			exit(EXIT_SUCCESS);
	}
	return (0);
}

void		hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 0, hook_keyon, mlx);
	mlx_hook(mlx->win, 4, 0, hook_mouseon, mlx);
	mlx_hook(mlx->win, 6, 0, hook_mouse_move, mlx);
	mlx_hook(mlx->win, 17, 0, close_button, mlx);
}
