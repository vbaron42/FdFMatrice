/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:50:50 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/23 06:16:48 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

void			center_points(t_env *env)
{
	int			height;
	int			len;
	double		s;

	height = WIN_HEIGHT / 3;
	len = (WIN_LEN + 100) / 2;
	env->center.x == 0 ? env->center.x = 10 : env->center.x;
	s = (len - 300) / (env->center.x);
	m_rlud(env, -env->center.x + len, -env->center.y + height);
	m_rot_x(env, -ROT_POW * 50);
	m_scale(env, s);
}

void			get_max(t_env *env, t_point *p)
{
	t_point		*tmp;
	int			i;

	i = 0;
	tmp = p;
	while (tmp != NULL)
	{
		if (env->xmax < tmp->x)
			env->xmax = tmp->x;
		if (env->ymax < tmp->y)
			env->ymax = tmp->y;
		if (env->zmax < tmp->z)
			env->zmax = tmp->z;
		tmp = tmp->next;
		i++;
	}
	if ((env->xmax + 1) * (env->zmax + 1) != i)
		ft_error("Invalid file, your map must be a rectangle\n");
}

void			init_map(t_env *env)
{
	color_map(env);
	map_center(env);
	get_max(env, env->p);
	center_points(env);
	draw_map(env->p, env);
}

int				main(int argc, char **argv)
{
	t_point		*p;
	t_env		*env;
	void		*mlx;
	void		*win;

	if (WIN_LEN > 2500 || WIN_HEIGHT > 1500
			|| WIN_LEN < 200 || WIN_HEIGHT < 200)
		ft_error("Choose a correct window size\n");
	if (argc != 2)
		ft_error("Usage : ./fdf file.fdf\n");
	if ((p = get_map(argv[1])) == NULL)
		ft_error("Empty file\n");
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		ft_error("Malloc error\n");
	if (!(env->mlx = mlx_init()))
		ft_error("mlx_init() error\n");
	if (!(env->win = mlx_new_window(env->mlx, WIN_LEN, WIN_HEIGHT, TITLE)))
		ft_error("mlx_new_window() error\n");
	env->img = new_img(env);
	env->p = p;
	init_map(env);
	mlx_key_hook(env->win, event, env);
	mlx_expose_hook(env->win, print_img, env);
	mlx_loop(env->mlx);
	return (0);
}
