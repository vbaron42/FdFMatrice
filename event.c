/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 02:32:14 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/23 06:04:49 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			key_hook(int code, t_env *env)
{
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
	if (code == 2)
		m_rlud(env, SPEED, 0);
	if (code == 0)
		m_rlud(env, -SPEED, 0);
	if (code == 1)
		m_rlud(env, 0, SPEED);
	if (code == 13)
		m_rlud(env, 0, -SPEED);
	if (code == 49)
		m_scale(env, 1 + SCALE_POWER);
	if (code == 257)
		m_scale(env, 1 - SCALE_POWER);
}

int				event(int code, t_env *env)
{
	if (code == 53)
	{
		mlx_destroy_window(env->mlx, env->win);
		exit(0);
	}
	key_hook(code, env);
	if (code == 8)
		env->dc = -env->dc;
	print_img(env);
	return (0);
}
