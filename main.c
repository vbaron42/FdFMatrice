/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:50:50 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/18 20:41:22 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

/*int				get_dim(int fd, int *xlen, int *zwid)
{
	int			gnl_ret;
	char		**str;
	char		**line;

	if (!(*line = ft_strnew(1)))
		return (-1);
	while ((gnl_ret = get_next_line(fd, line)) > 0)
	{
		str = ft_strsplit(*line, ' ');//ft_free line et str ?
		while (str[*xlen] != NULL)
			*xlen++;
		*zwid++;
	}
	return (gnl_ret);
}
*/
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
t_point				ortho_to_iso(t_point ort_p, t_env env)
{
	t_point			iso_p;

	iso_p = ort_p;
	iso_p.z = ort_p.y;
	iso_p.x = (ort_p.x - ort_p.z) * (env.scale / 2);
	iso_p.y = (ort_p.x + ort_p.z - (ort_p.y)) * (env.scale / 2);
	iso_p.x += WIN_LEN / 2;
	iso_p.y += WIN_HEIGHT / 10;
	return (iso_p);
}*/

/*t_tab			**keep_value(t_point *p, t_env *env)//utile ? :/
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
}*/

int				main(int argc, char **argv)
{
	t_point		*p;
	t_point		*tmp;
	t_env		*env;
//	t_tab		**tab;
	int			prevx;
	int			prevz;
	void		*mlx;
	void		*win;

	if (argc != 2 || (p = get_map(argv[1])) == NULL)
		return (-1);
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (-1);
//	env->p = p;
//	&p = env;//ajout de p dans env
	env->rl = 0;
	env->ud = 0;
	if (!(env->mlx = mlx_init()))
		return (-1);
	if (!(env->win = mlx_new_window(env->mlx, WIN_LEN, WIN_HEIGHT, "title")))
		return (-1);
	if (!(env->img = new_img(env)))
		return (-1);
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
	env->scale = WIN_LEN / (env->xmax + env->zmax / 2);
/*	env->scale = 1;
	while (WIN_HEIGHT / 2 > map->h * env->scale
				&& WIN_LEN / 2 > map->l * env->scale
				&& env->scale < SCALE_MAX)
		env->scale += 1;*/
	env->p = p;
	tmp = env->p;
	while (tmp != NULL)
	{
		ft_putnbr(tmp->y);
//		*tmp = ortho_to_iso(*tmp, *env);
		tmp = tmp->next;
	}
	if (draw_map(p, env) == -1)
		return (-1);//fermer la fenetre et exit
//	env->tab = keep_value(p, env);
	ft_putstr("hook entrance :\n");
	mlx_key_hook(env->win, event, env);// a chaque fois p reprendra la valeur de tab * matri
	mlx_expose_hook(env->win, print_img, env);
	mlx_loop(env->mlx);
	return (0);
}
