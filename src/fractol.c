/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 18:52:55 by bmontoya          #+#    #+#             */
/*   Updated: 2017/06/28 18:07:23 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <ftstdio.h>
#include <ftstring.h>
#include <pthread.h>
#include <mlx.h>
#define FL_INVALID "usage: ./fractol [fractol]\nValid fractols:"
#define FL_VALID "julia\nmandlebrot\nsierpinski"

void	*fl_thread(void *venv)
{
	t_env	*env;

	env = (t_env *)venv;
	if (pthread_equal(pthread_self(), env->thread[0]))
		env->fract(env, 0, HEIGHT / 8);
	else if (pthread_equal(pthread_self(), env->thread[1]))
		env->fract(env, HEIGHT / 8, HEIGHT * 2 / 8);
	else if (pthread_equal(pthread_self(), env->thread[2]))
		env->fract(env, HEIGHT * 2 / 8, HEIGHT * 3 / 8);
	else if (pthread_equal(pthread_self(), env->thread[3]))
		env->fract(env, HEIGHT * 3 / 8, HEIGHT * 4 / 8);
	else if (pthread_equal(pthread_self(), env->thread[4]))
		env->fract(env, HEIGHT * 4 / 8, HEIGHT * 5 / 8);
	else if (pthread_equal(pthread_self(), env->thread[5]))
		env->fract(env, HEIGHT * 5 / 8, HEIGHT * 6 / 8);
	else if (pthread_equal(pthread_self(), env->thread[6]))
		env->fract(env, HEIGHT * 6 / 8, HEIGHT * 7 / 8);
	else if (pthread_equal(pthread_self(), env->thread[7]))
		env->fract(env, HEIGHT * 7 / 8, HEIGHT);
	pthread_exit(0);
	return (NULL);
}

int		fl_select_fractol(t_env *env, char *fractol)
{
	if (!ft_strcmp(fractol, "julia"))
		env->fract = &fl_julia;
	else if (!ft_strcmp(fractol, "mandlebrot"))
		env->fract = &fl_mandlebrot;
	else if (!ft_strcmp(fractol, "sierpinski"))
		env->fract = &fl_sierpinski;
	else
		return (0);
	env->xcenter = 0;
	env->ycenter = 0;
	env->xoff = HWIDTH;
	env->yoff = HHEIGHT;
	env->xzoom = HWIDTH * DZOOM;
	env->yzoom = HHEIGHT * DZOOM;
	if (env->fract == &fl_sierpinski)
	{
		env->xzoom = DZOOM;
		env->yzoom = DZOOM;
		env->xoff = 0;
		env->yoff = 0;
	}
	env->maxiters = 50;
	env->cdiv = 0xFFFFFF / env->maxiters;
	return (1);
}

int		main(int argc, char **argv)
{
	t_env	env;

	if (argc == 2 && fl_select_fractol(&env, argv[1]))
	{
		env.mlx = mlx_init();
		env.win = mlx_new_window(env.mlx, WIDTH, HEIGHT, "fractol 42");
		env.img = mlx_new_image(env.mlx, WIDTH, HEIGHT);
		env.imgp = (int *)mlx_get_data_addr(env.img, &env.bpp,
		&env.lsize, &env.endian);
		mlx_expose_hook(env.win, &fl_expose_hook, &env);
		mlx_mouse_hook(env.win, &fl_mouse_hook, &env);
		mlx_hook(env.win, 6, 0, &fl_motion_hook, &env);
		mlx_hook(env.win, 2, 0, &fl_key_hook, &env);
		mlx_loop(env.mlx);
	}
	else
		ft_printf("%s\n%s\n", FL_INVALID, FL_VALID);
}
