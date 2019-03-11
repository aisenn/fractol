/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aabdulla <aabdulla@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 15:17:24 by aabdulla          #+#    #+#             */
/*   Updated: 2019/02/18 15:17:27 by aabdulla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include "../libft/includes/libft.h"
# include <pthread.h>

# define M_WIDTH (600)
# define M_HEIGHT (600)

# define WIDTH (640)
# define HEIGHT (480)
# define AMOUNT_OF_THREADS 4

# define KEY_ESC 53
# define KEY_TAB 48
# define KEY_SPACE 49
# define KEY_PLUS 27
# define KEY_MINUS 24
# define NUM_PLUS 69
# define NUM_MINUS 78
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_R 15
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_SHIFT 257
# define PAGE_UP 116
# define PAGE_DOWN 121

typedef struct			s_pix
{
	int					i;
	double				zn;
}						t_pix;

typedef struct			s_col
{
	double				r;
	double				g;
	double				b;
}						t_col;

typedef struct			s_palette
{
	int					c;
	int					colors[16];
	struct s_palette	*next;
	struct s_palette	*previous;
}						t_palette;

typedef struct			s_ctrl
{
	int					key;
}						t_ctrl;

typedef struct			s_mlx
{
	void				*win;
	void				*mlx;
	void				*img;
	char				*data;
	int					bpp;
	int					sl;
	int					end;
	double				re_min;
	double				re_max;
	double				im_min;
	double				im_max;
	int					max_iter;
	int					n;
	t_ctrl				*ctrl;
	double				jul_re;
	double				jul_im;
	char				*name;
	int					smooth;
	t_palette			*palette;
	int					check;
	int					menu;
	char				*old_data;
}						t_mlx;

typedef struct			s_frac
{
	int					max_iter;
	int					n;
	double				z_re;
	double				z_im;
	double				c_re;
	double				c_im;
	double				jul_re;
	double				jul_im;
	void				(*iter_fn)(struct s_frac *);
	t_pix				pix;
}						t_frac;

typedef struct			s_th
{
	int					i;
	t_mlx				*mlx;
	t_frac				*frac;
}						t_th;

int						hook_mouse_move(int x, int y, t_mlx *mlx);
int						get_color(t_mlx *mlx, t_pix *pix);
int						hook_mouseon(int click, int x, int y, t_mlx *mlx);
int						window_split(t_mlx *mlx);
t_palette				*get_palette(void);
void					information(void);
void					hooks(t_mlx *mlx);
void					set_fractal(t_mlx *mlx);

void					mandelbrot_iter(t_frac *frac);
void					julia_iter(t_frac *frac);
void					tricorn_iter(t_frac *frac);
void					pentocorn_iter(t_frac *frac);
void					celtic_iter(t_frac *frac);
void					mandelbrot4_iter(t_frac *frac);
void					cmandelbar_iter(t_frac *frac);
void					burningship_iter(t_frac *frac);
void					trijulia_iter(t_frac *frac);
void					necklace_iter(t_frac *frac);

void					destroy_window(t_mlx *mlx);
int						fractals_init(int is_menu, char *argv);
int						menu(t_mlx *mlx);

void					menu_hooks(t_mlx *mlx);

int						ft_usage(char *str);
void					information(void);
void					active(t_mlx *mlx, int x, int y, char c);
void					toggle_info(t_mlx *mlx, int x, int y);
#endif
