/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/04 19:46:57 by bmontoya          #+#    #+#             */
/*   Updated: 2017/07/02 14:54:55 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include <pthread.h>
# define WIDTH 1000
# define HEIGHT 1000
# define HHEIGHT HEIGHT / 2
# define HWIDTH WIDTH / 2
# define DZOOM .25

typedef struct	s_complex
{
	double		x;
	double		yi;
}				t_complex;

typedef void	(*t_fract)();

typedef struct	s_env
{
	pthread_t	thread[8];
	t_complex	c;
	void		*mlx;
	void		*win;
	void		*img;
	int			*imgp;
	int			bpp;
	int			lsize;
	int			endian;
	double		xcenter;
	double		ycenter;
	double		xzoom;
	double		yzoom;
	double		cdiv;
	t_fract		fract;
	int			xoff;
	int			yoff;
	int			maxiters;
}				t_env;

void			fl_julia(t_env *env, int y, int yend);
void			fl_mandlebrot(t_env *env, int y, int yend);
void			fl_sierpinski(t_env *env, int y, int yend);
void			fl_cdiv(t_complex *num, t_complex *dem);
t_complex		*fl_cadd(t_complex *dst, const t_complex *src);
t_complex		*fl_cpow_2(t_complex *src);
void			fl_cmult(t_complex *dst, t_complex *src);
void			*fl_thread(void *venv);
int				fl_motion_hook(int x, int y, t_env *env);
int				fl_mouse_hook(int button, int x, int y, t_env *env);
int				fl_expose_hook(t_env *env);
int				fl_key_hook(int button, t_env *env);
#endif
