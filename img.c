/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/16 22:36:55 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/18 20:48:28 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_img		*new_img(t_env *env)
{
	t_img	*img;

	if (!(img = (t_img*)malloc(sizeof(t_img))))
		return (NULL);
	img->ptr = mlx_new_image(env->mlx, WIN_LEN, WIN_HEIGHT);
	img->pxl_byt = mlx_get_data_addr(img->ptr, &img->bpp,
			&img->line_size, &img->endian);
	return (img);
}

int			print_img(t_env *env)
{
	t_point	*tmp;

	mlx_destroy_image(env->mlx, env->img->ptr);
	if (!(env->img = new_img(env)))
		exit(1);
	draw_map(env->p, env);// p sera matrice(p, move)
	tmp = env->p;//
	while (tmp != NULL)
	{
		ft_putnbr(tmp->y);
		tmp = tmp->next;
	}//
	mlx_clear_window(env->mlx, env->win);
	mlx_put_image_to_window(env->mlx, env->win, env->img->ptr, 0, 0);
//	display_info(env); (affichage supplementaire)
	ft_putstr("img print !");
	return (1);
}
