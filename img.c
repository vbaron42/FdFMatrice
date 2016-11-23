/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 22:36:55 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/23 06:15:42 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		display_controls(t_env *env)
{
	mlx_string_put(env->mlx, env->win, 100, 40, 0xFF5FFF, "Controls:");
	mlx_string_put(env->mlx, env->win, 120, 80, 0xFFFFFF,
			"-Use W-A-S-D to move up/left/down/right");
	mlx_string_put(env->mlx, env->win, 120, 110, 0xFFFFFF,
			"-Use Space and Shift to Zoom in/out");
	mlx_string_put(env->mlx, env->win, 120, 140, 0xFFFFFF,
			"-Rotate in y/x/z with 4/+, 5/8, 6/9");
	mlx_string_put(env->mlx, env->win, 120, 170, 0xFFFFFF,
			"-Use C to turn on/off default color");
	mlx_string_put(env->mlx, env->win, 120, 200, 0xFFFFFF,
			"-Use Esc to quit");
}

t_img		*new_img(t_env *env)
{
	t_img	*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		ft_error("Malloc error\n");
	if (!(img->ptr = mlx_new_image(env->mlx, WIN_LEN, WIN_HEIGHT)))
		ft_error("mlx_new_image() error\n");
	if (!(img->pxl_byt = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_size, &img->endian)))
		ft_error("mlx_get_data_addr() error\n");
	return (img);
}

int			print_img(t_env *env)
{
	mlx_destroy_image(env->mlx, env->img->ptr);
	env->img = new_img(env);
	draw_map(env->p, env);
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->img->ptr, 0, 0);
	display_controls(env);
	return (1);
}
