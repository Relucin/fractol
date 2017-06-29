/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fl_complex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmontoya <bmontoya@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 19:58:27 by bmontoya          #+#    #+#             */
/*   Updated: 2017/06/25 15:47:57 by bmontoya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fractol.h>
#include <ftstring.h>

inline t_complex	*fl_cadd(t_complex *dst, const t_complex *src)
{
	dst->x += src->x;
	dst->yi += src->yi;
	return (dst);
}

inline void			fl_cdiv(t_complex *num, t_complex *dem)
{
	t_complex	demi;

	ft_memcpy(&demi, dem, sizeof(t_complex));
	demi.yi *= -1;
	fl_cmult(num, &demi);
	demi.x *= demi.x;
	demi.yi *= demi.yi;
	if (demi.x != demi.yi)
	{
		if (num->x)
			num->x /= (demi.x - demi.yi);
		if (num->yi)
			num->yi /= (demi.x - demi.yi);
	}
}

inline void			fl_cmult(t_complex *dst, t_complex *src)
{
	double	tx;

	tx = dst->x * src->x - dst->yi * src->yi;
	dst->yi = dst->x * src->yi + src->x * dst->yi;
	dst->x = tx;
}

inline t_complex	*fl_cpow_2(t_complex *src)
{
	double	tx;

	tx = src->x * src->x - src->yi * src->yi;
	src->yi = 2 * src->x * src->yi;
	src->x = tx;
	return (src);
}
