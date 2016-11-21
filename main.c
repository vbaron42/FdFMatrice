/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:50:50 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/21 21:54:44 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

t_point			*ft_lstadd_p(t_point *p, int x, char *str, int z)
{
	t_point		*newp;
	t_point		*tmp;

	newp = (t_point *)malloc(sizeof(t_point));
	newp->x = x;
	newp->y = ft_atoi(str);
	newp->z = z;
	newp->c = ft_atoi_16(str);
	if ((newp->c = ft_atoi_16(str)) == 0)
		newp->c = 0xFFFFFF;
	if (newp)
		newp->next = NULL;
	if (p == NULL)
		return (newp);
	tmp = p;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = newp;
	return (p);
}

t_point			*fill_p(int fd)
{
	t_point		*p;
	char		**str;
	char		*line;
	int			x;
	int			z;

	p = NULL;
	if (!(line = ft_strnew(1)))
		return (NULL);
	z = 0;
	while ((x = get_next_line(fd, &line)) != 0)
	{
		if (x == -1)
			return (NULL);
		x = 0;
		str = ft_strsplit_mo(line, ' ', '	', ' ');//ft_free str et line ?
		while (str[x] != NULL)
		{
			p = ft_lstadd_p(p, x, str[x], z);
			x++;
		}
		z++;
	}
	return (p);
}

t_point			*get_map(char *file)
{
	int			fd;
	t_point		*p;

	if ((!(ft_strstr(file, ".fdf")))
			|| (fd = open(file, O_RDONLY)) == -1
			|| (!(p = fill_p(fd))))
		return (NULL);
	close(fd);
	return (p);
}

/*
t_tab			**keep_value(t_point *p, t_env *env)//utile ? :/
{
	t_tab		**tab;
	int			i;
	int			i2;

	i = -1;
	if (!(tab = (t_tab**)malloc((zmax + 1) * sizeof(tab*))))
			return (NULL);
	while (i++ <= env->zmax)
	{
		if (!(tab[i] = (t_tab*)malloc((env->xmax + 1) * sizeof(tab))))
			return (NULL);
		i2 = -1;
		while (i2++ <= env->xmax)
		{
			tab[i][i2]->x = p->x;
			tab[i][i2]->y = p->y;
			tab[i][i2]->z = p->z;
			tab[i][i2]->w = 1;//utile ? (surement)
			p = p->next;
		}
	}
	return (tab);
}
*/

void			center_points(t_env *env)
{
	int			height;
	int			len;
	double		s;

	height = (WIN_HEIGHT + 100) / 2;
	len = (WIN_LEN + 100) / 2;
	env->center.x == 0 ? env->center.x = 10 : env->center.x;
	s = (len - 100) / (env->center.x);
	ft_putstr("\n\n\n");
	ft_putnbr(-env->center.y + height);
	m_rlud(env, -env->center.x + len, -env->center.y + height);
	m_scale(env, s);
}

void			get_max(t_env *env, t_point *p)
{
	t_point		*tmp;

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
	}
}

int				main(int argc, char **argv)
{
	t_point		*p;
	t_env		*env;
	void		*mlx;
	void		*win;
//	t_tab		**tab;

	if (argc != 2 || (p = get_map(argv[1])) == NULL)
		return (-1);
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (-1);
	env->rl = 0;
	env->ud = 0;
	if (!(env->mlx = mlx_init()))
		return (-1);
	if (!(env->win = mlx_new_window(env->mlx, WIN_LEN, WIN_HEIGHT, "title")))
		return (-1);
	if (!(env->img = new_img(env)))
		return (-1);
/*	env->scale = 1;
	while (WIN_HEIGHT / 2 > map->h * env->scale
				&& WIN_LEN / 2 > map->l * env->scale
				&& env->scale < SCALE_MAX)
		env->scale += 1;*/
	env->p = p;
	map_center(env);
	get_max(env, env->p);
	center_points(env);
	if (draw_map(p, env) == -1)
		return (-1);//fermer la fenetre et exit
//	env->tab = keep_value(p, env);
	ft_putstr("hook entrance :\n");
	mlx_key_hook(env->win, event, env);
	mlx_expose_hook(env->win, print_img, env);
	mlx_loop(env->mlx);
	return (0);
}
