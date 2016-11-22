/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segment_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/11 19:10:30 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/23 00:05:47 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void				img_put_pixel(t_env *env, t_point *p, int c)
{
	int				pxl;

	if (p->y < WIN_HEIGHT && p->x < WIN_LEN
			&& p->y > 0 && p->x > 0)
	{
		pxl = (p->y) * env->img->line_size + (env->img->bpp / 8) * (p->x);
		env->img->pxl_byt[pxl] = c;
		env->img->pxl_byt[++pxl] = c >> 8;
		env->img->pxl_byt[++pxl] = c >> 16;
	}
}

t_line_data			*new_ldata(t_point a, t_point b)
{
	t_line_data		*l;

	if (!(l = (t_line_data*)malloc(sizeof(t_line_data))))
		return (NULL);
	l->dx = ft_abs(b.x - a.x);
	l->dy = ft_abs(b.y - a.y);
	l->ix = (a.x < b.x) ? 1 : -1;
	l->iy = (a.y < b.y) ? 1 : -1;
	l->err = (l->dx > l->dy) ? l->dx / 2 : -l->dy / 2;
	return (l);
}

t_point				double_to_int(t_point a)
{
	a.x = (int)a.x;
	a.y = (int)a.y;
	return (a);
}

void				segment_put(t_env *env, t_point a, t_point b)
{
	t_line_data		*l;

	a = double_to_int(a);
	b = double_to_int(b);
	if (!(l = new_ldata(a, b)))
		return (-1);
	while (42)
	{
		choose_color(env, a, b);
		if (a.x == b.x && a.y == b.y)
			break ;
		l->e = l->err;
		if (l->e > -l->dx)
		{
			l->err -= l->dy;
			a.x += l->ix;
		}
		if (l->e < l->dy)
		{
			l->err += l->dx;
			a.y += l->iy;
		}
	}
}

/*
**	free ldata
*/

void				draw_map(t_point *p, t_env *env)
{
	t_point			*pnext;
	t_point			*pdown;
	int				i;

	i = env->xmax + 1;
	pnext = p->next;
	pdown = p->next;
	while (i-- > 1)
		pdown = pdown->next;
	while (pnext != NULL)
	{
		if (pdown != NULL)
			segment_put(env, *p, *pdown);
		if (i++ < env->xmax)
			segment_put(env, *p, *pnext);
		else
			i = 0;
		p = p->next;
		pnext = pnext->next;
		if (pdown != NULL)
			pdown = pdown->next;
	}
}
