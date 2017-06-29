/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_fractols.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 19:06:37 by bmontoya          #+#    #+#             */
/*   Updated: 2017/06/27 14:26:08 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <ftstring.h>
#include <math.h>
#include <stdlib.h>
#include <inttypes.h>

void		fl_mandlebrot(t_env *env, int y, int yend)
{
	t_complex	c;
	t_complex	z;
	int			x;
	int			iters;

	while (y < yend)
	{
		x = 0;
		while (x < WIDTH)
		{
			iters = 0;
			c.x = (x - env->xoff) / env->xzoom + env->xcenter;
			c.yi = (y - env->yoff) / env->yzoom + env->ycenter;
			ft_memcpy(&z, &c, sizeof(c));
			while (++iters < env->maxiters)
			{
				fl_cadd(fl_cpow_2(&z), &c);
				if ((z.x * z.x + z.yi * z.yi) > 4)
					break ;
			}
			env->imgp[x + y * HEIGHT] = (env->maxiters - iters) * env->cdiv;
			++x;
		}
		++y;
	}
}

void		fl_julia(t_env *env, int y, int yend)
{
	t_complex	z;
	int			x;
	int			iters;

	while (y < yend)
	{
		x = 0;
		while (x < WIDTH)
		{
			iters = 0;
			z.x = (x - env->xoff) / env->xzoom + env->xcenter;
			z.yi = (y - env->yoff) / env->yzoom + env->ycenter;
			while (iters < env->maxiters)
			{
				fl_cadd(fl_cpow_2(&z), &env->c);
				if ((z.x * z.x + z.yi * z.yi) > 4)
					break ;
				++iters;
			}
			env->imgp[x + y * HEIGHT] = (env->maxiters - iters) * env->cdiv;
			++x;
		}
		++y;
	}
}

inline int	fl_sierpinski_color(intmax_t nx, intmax_t ny)
{
	while (1)
	{
		if (nx == 0 || ny == 0)
			return (0);
		if (nx % 3 == 1 && ny % 3 == 1)
			return (0xFFFFFF);
		nx /= 3;
		ny /= 3;
	}
}

void		fl_sierpinski(t_env *env, int y, int yend)
{
	int			x;
	intmax_t	nx;
	intmax_t	ny;

	while (y < yend)
	{
		x = 0;
		while (x < WIDTH)
		{
			nx = (x - env->xoff) / env->xzoom + env->xcenter;
			ny = (y - env->yoff) / env->yzoom + env->ycenter;
			env->imgp[x + y * HEIGHT] =
			fl_sierpinski_color(imaxabs(nx), imaxabs(ny));
			++x;
		}
		++y;
	}
}
