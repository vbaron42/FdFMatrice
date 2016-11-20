/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/17 02:32:14 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/20 15:34:55 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int				key_hook(int code, t_env *env)
{
	t_point		*tmp;

	tmp = env->p;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->y);
		tmp = tmp->next;
	}
//ajouter les rotations ici;
	if (code == 2)
		/*env->p = */m_rlud(env, SPEED, 0);
	ft_putstr("1ere matrice passe");
	if (code == 0)
		/*env->p = */m_rlud(env, -SPEED, 0);
	if (code == 49)
		/*env->p = */m_rlud(env, 0, SPEED);
	if (code == 257)
		/*env->p = */m_rlud(env, 0, -SPEED);
	if (code == 13)
		/*env->p = */m_scale(env, 1 + SCALE_POWER);
	if (code == 1)
		/*env->p = */m_scale(env, 1 - SCALE_POWER);
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
