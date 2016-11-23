/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_matrice.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 05:22:31 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/23 05:23:37 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			m_rot_y(t_env *env, double x)
{
	t_matrice	*m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		ft_error("Malloc error\n");
	m->a = cos(x);
	m->c = sin(x);
	m->i = -sin(x);
	m->k = cos(x);
	m->f = 1;
	m->h = 1;
	matrice(env, m);
	free(m);
}

void			m_rot_x(t_env *env, double x)
{
	t_matrice	*m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		ft_error("Malloc error\n");
	m->a = 1;
	m->f = cos(x);
	m->g = -sin(x);
	m->j = sin(x);
	m->k = cos(x);
	matrice(env, m);
	free(m);
}

void			m_rot_z(t_env *env, double x)
{
	t_matrice	*m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		ft_error("Malloc error\n");
	m->a = cos(x);
	m->b = -sin(x);
	m->e = sin(x);
	m->f = cos(x);
	m->k = 1;
	matrice(env, m);
	free(m);
}

void			m_rlud(t_env *env, double x, double y)
{
	t_matrice	*m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		ft_error("Malloc error\n");
	m->d = x;
	m->h = y;
	m->l = 0;
	m->a = 1;
	m->f = 1;
	m->k = 1;
	matrice(env, m);
	map_center(env);
	free(m);
}

void			m_scale(t_env *env, double s)
{
	t_matrice	*m;

	if (!(m = (t_matrice*)ft_memalloc(sizeof(t_matrice))))
		ft_error("Malloc error\n");
	m->a = s;
	m->f = s;
	m->k = s;
	matrice(env, m);
	free(m);
}
