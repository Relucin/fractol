/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_hooks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 20:47:59 by bmontoya          #+#    #+#             */
/*   Updated: 2017/06/28 18:04:45 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <pthread.h>
#include <stdlib.h>
#include <mlx.h>
#define ZOOMSPEED 1.1
#define MOVE 10

int		fl_expose_hook(t_env *env)
{
	pthread_create(env->thread, NULL, fl_thread, env);
	pthread_create(env->thread + 1, NULL, fl_thread, env);
	pthread_create(env->thread + 2, NULL, fl_thread, env);
	pthread_create(env->thread + 3, NULL, fl_thread, env);
	pthread_create(env->thread + 4, NULL, fl_thread, env);
	pthread_create(env->thread + 5, NULL, fl_thread, env);
	pthread_create(env->thread + 6, NULL, fl_thread, env);
	pthread_create(env->thread + 7, NULL, fl_thread, env);
	pthread_join(env->thread[0], NULL);
	pthread_join(env->thread[1], NULL);
	pthread_join(env->thread[2], NULL);
	pthread_join(env->thread[3], NULL);
	pthread_join(env->thread[4], NULL);
	pthread_join(env->thread[5], NULL);
	pthread_join(env->thread[6], NULL);
	pthread_join(env->thread[7], NULL);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
	return (0);
}

int		fl_mouse_hook(int button, int x, int y, t_env *env)
{
	if (button == 4 || button == 5)
	{
		env->xcenter += (x - env->xoff) / env->xzoom;
		env->ycenter += (y - env->yoff) / env->yzoom;
		if ((button == 5) || button == 4)
		{
			env->xzoom *= (button == 4) ? ZOOMSPEED : 1 / ZOOMSPEED;
			env->yzoom *= (button == 4) ? ZOOMSPEED : 1 / ZOOMSPEED;
		}
		env->xoff = x;
		env->yoff = y;
		fl_expose_hook(env);
	}
	return (0);
}

int		fl_motion_hook(int x, int y, t_env *env)
{
	static int	xprev;
	static int	yprev;
	double		xmove;
	double		ymove;

	if (env->fract == &fl_julia)
	{
		xmove = .01 * (500 / env->xzoom);
		ymove = .01 * (500 / env->yzoom);
		if (x - xprev)
			env->c.x += (x - xprev > 0) ? xmove : -xmove;
		if (y - yprev)
			env->c.yi += (y - yprev > 0) ? ymove : -ymove;
		fl_expose_hook(env);
		xprev = x;
		yprev = y;
	}
	return (0);
}

void	fl_exit(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img);
	mlx_destroy_window(env->mlx, env->win);
	exit(EXIT_SUCCESS);
}

int		fl_key_hook(int button, t_env *env)
{
	if (button == 124 || button == 123)
	{
		env->xoff += (button == 124) ? MOVE : -MOVE;
		fl_expose_hook(env);
	}
	else if (button == 125 || button == 126)
	{
		env->yoff += (button == 125) ? MOVE : -MOVE;
		fl_expose_hook(env);
	}
	else if (button == 15)
	{
		env->xzoom = ((env->fract == &fl_sierpinski) ? 1 : HWIDTH) * DZOOM;
		env->yzoom = ((env->fract == &fl_sierpinski) ? 1 : HHEIGHT) * DZOOM;
		env->xoff = HWIDTH;
		env->yoff = HHEIGHT;
		env->xcenter = 0;
		env->ycenter = 0;
		fl_expose_hook(env);
	}
	else if (button == 53)
		fl_exit(env);
	return (0);
}
