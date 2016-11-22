/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 03:12:00 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/22 18:05:01 by vbaron           ###   ########.fr       */
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
	ft_putchar('\n');
	ft_putnbr(center.x);
	ft_putchar('\n');
	ft_putnbr(center.y);
	env->center = center;
}

t_point			*matricialisation(t_env *env, t_point *p, t_matrice *m)
{
	double		x;
	double		y;
	double		z;
	double		w;

	p->x -= env->center.x;//trouver la valeur de cx et cy (env->center.x)
	p->y -= env->center.y;
	w = 1;//trouver la valeur de w (s)
	//env->center.x = x;
	//env->center.y = y;
	x = (m->a * p->x + m->b * p->y + m->c * p->z + m->d * w);
	y = (m->e * p->x + m->f * p->y + m->g * p->z + m->h * w);
	z = (m->i * p->x + m->j * p->y + m->k * p->z + m->l * w);//p->w ne change pas :)
	p->x = x;
	p->y = y;
	p->z = z;
	ft_putnbr(x);
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
//	return (env->p);
}

void			m_rot_y(t_env *env, double x)
{
	t_matrice	*m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		;//ft_error();
	m->a = cos(x);
	m->c = sin(x);
	m->i = -sin(x);
	m->k = cos(x);
	m->f = 1;
	m->h = 1;
	matrice(env, m);
	free(m);
}

void			m_rlud(t_env *env, double x, double y)
{
	t_matrice	*m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		;//ft_error();
	m->d = x;
	m->h = y;
	m->l = 0;
	m->a = 1;
	m->f = 1;
	m->k = 1;
	m->p = 1;
	matrice(env, m);
	map_center(env);
	free(m);
}

void			m_scale(t_env *env, double s)
{
	t_matrice	*m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		;//ft_error();
	m->a = s;
	m->f = s;
	m->k = s;
	m->p = 1;//qu est ce que fou ce p ici ???
	matrice(env, m);
	free(m);
}
