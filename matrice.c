/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrice.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 03:12:00 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/20 16:02:15 by vbaron           ###   ########.fr       */
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
	t_point		*tmp;

	x = p->x - env->center.x;//trouver la valeur de cx et cy (env->center.x)
	y = p->y - env->center.y;
	z = p->z;
	w = 1;//trouver la valeur de w (s)
	env->center.x = x;
	env->center.y = y;
	p->x = (m->a * x + m->b * y + m->c * z + m->d * w);
	p->y = (m->e * x + m->f * y + m->g * z + m->h * w);
	p->z = (m->i * x + m->j * y + m->k * z + m->l * w);//p->w ne change pas :)
	p->x += env->center.x;
	p->y += env->center.y;
	return (p);
	tmp = env->p;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->y);
//		*tmp = ortho_to_iso(*tmp, *env);
		tmp = tmp->next;
	}
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

void			m_rlud(t_env *env, double x, double y)
{
	t_matrice	*m;
	t_point		*p2;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		/*return (NULL)*/;//fdf_malloc_error();
	m->d = x;
	m->h = y;
	m->l = 0;
	m->a = 1;
	m->f = 1;
	m->k = 1;
	m->p = 1;
	ft_putstr("entree dans la matrice\n\n");
	matrice(env, m);
	ft_putstr("wtf");
	ft_putnbr(env->p->y);
//	ft_putnbr(env->p->next->y);
	ft_putstr("ok, that s better");
	//get_center(e); ... toi tu va me les peter ...
	free(m);
//	return (env->p);
}

void			m_scale(t_env *env, double s)
{
	t_matrice	*m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		/*return (NULL)*/;//fdf_malloc_error();
	m->a = s;
	m->f = s;
	m->k = s;
	m->p = 1;
	/*env->p = */matrice(env, m);
	free(m);
//	return (env->p);
}
