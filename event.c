/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 02:32:14 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/22 20:51:31 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				key_hook(int code, t_env *env)
{
	t_point		*tmp;

	ft_putnbr(code);
	tmp = env->p;
	if (code == 86)
		m_rot_y(env, ROT_POW);
	if (code == 69)
		m_rot_y(env, -ROT_POW);
	if (code == 91)
		m_rot_x(env, ROT_POW);
	if (code == 87)
		m_rot_x(env, -ROT_POW);
	if (code == 92)
		m_rot_z(env, ROT_POW);
	if (code == 88)
		m_rot_z(env, -ROT_POW);
//ajouter les rotations ici;
	if (code == 0)
		/*env->p = */m_rlud(env, SPEED, 0);
	if (code == 2)
		/*env->p = */m_rlud(env, -SPEED, 0);
	if (code == 49)
		/*env->p = */m_rlud(env, 0, SPEED);
	if (code == 257)
		/*env->p = */m_rlud(env, 0, -SPEED);
	if (code == 13)
		/*env->p = */m_scale(env, 1 + SCALE_POWER);
	if (code == 1)
		/*env->p = */m_scale(env, 1 - SCALE_POWER);
	if (code == 8)
		env->dc = -env->dc;
	return (0);
}//colorier soit meme la map :) avec le curseur et les touches

int				event(int code, t_env *env)
{
	if (code == 53)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	key_hook(code, env);
	print_img(env);
	return (0);
}
