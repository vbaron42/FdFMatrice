/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 03:12:00 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/23 05:23:06 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			map_center(t_env *env)
{
	t_point		center;
	t_point		*tmp;

	tmp = env->p;
	while (tmp->next != NULL)
		tmp = tmp->next;
	center.x = (tmp->x + env->p->x) / 2;
	center.y = (tmp->y + env->p->y) / 2;
	env->center = center;
}

t_point			*matricialisation(t_env *env, t_point *p, t_matrice *m)
{
	double		x;
	double		y;
	double		z;
	double		w;

	p->x -= env->center.x;
	p->y -= env->center.y;
	w = 1;
	x = (m->a * p->x + m->b * p->y + m->c * p->z + m->d * w);
	y = (m->e * p->x + m->f * p->y + m->g * p->z + m->h * w);
	z = (m->i * p->x + m->j * p->y + m->k * p->z + m->l * w);
	p->x = x;
	p->y = y;
	p->z = z;
	p->x += env->center.x;
	p->y += env->center.y;
	return (p);
}

void			matrice(t_env *env, t_matrice *m)
{
	t_point		*tmp;
	int			i;
	int			i2;

	tmp = env->p;
	i = -1;
	while (i++ < env->zmax)
	{
		i2 = -1;
		while (i2++ < env->xmax)
		{
			tmp = matricialisation(env, tmp, m);
			tmp = tmp->next;
		}
	}
}
