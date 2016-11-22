/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 20:13:37 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/22 20:32:47 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			color_map(t_env *env)
{
	t_point		*tmp;

	tmp = env->p;
	while (tmp != NULL)
	{
		if (tmp->y <= 0)
			tmp->dc = 0x00CCFF;
		if (tmp->y > 0 && tmp->y <= 2)
			tmp->dc = 0xFFCC33;
		if (tmp->y > 2 && tmp->y <= 4)
			tmp->dc = 0xFF9933;
		if (tmp->y > 4 && tmp->y <= 10)
			tmp->dc = 0x336600;
		if (tmp->y > 10 && tmp->y <= 14)
			tmp->dc = 0x999999;
		if (tmp->y > 14)
			tmp->dc = 0xCCFFFF;
		tmp = tmp->next;
	}
	env->dc = -1;
}

void			choose_color(t_env *env, t_point a, t_point b)
{
	if (b.z > a.z)
	{
		if (env->dc == 1)
			img_put_pixel(env, &a, b.dc);
		else
			img_put_pixel(env, &a, b.c);
	}
	else
	{
		if (env->dc == 1)
			img_put_pixel(env, &a, a.dc);
		else
			img_put_pixel(env, &a, a.c);
	}
}
