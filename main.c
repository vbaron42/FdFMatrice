/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:50:50 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/22 22:50:55 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>

t_point			*ft_lstadd_p(t_point *p, int x, char *str, int z)
{
	t_point		*newp;
	t_point		*tmp;

	if ((newp = (t_point *)malloc(sizeof(t_point))) == NULL)
		;//ft_error
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
		str = ft_strsplit_mo(line, ' ', '	', ' ');
		while (str[x] != NULL)//Attention crash en cas d'insertion de caractere
		{//chercher d ou vient le probleme (surement ici)
			p = ft_lstadd_p(p, x, str[x], z);
			free(str[x]);
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

void			center_points(t_env *env)
{
	int			height;
	int			len;
	double		s;

	height = WIN_HEIGHT / 3;
	len = (WIN_LEN + 100) / 2;
	env->center.x == 0 ? env->center.x = 10 : env->center.x;
	s = (len - 300) / (env->center.x);
	ft_putstr("\n\n\n");
	ft_putnbr(-env->center.y + height);
	m_rlud(env, -env->center.x + len, -env->center.y + height);
	m_rot_x(env, -ROT_POW * 50);
	m_scale(env, s);
}

int				get_max(t_env *env, t_point *p)
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
		return (0);
	return (1);
}

int				main(int argc, char **argv)
{
	t_point		*p;
	t_env		*env;
	void		*mlx;
	void		*win;

	if (WIN_LEN > 2500 || WIN_HEIGHT > 1500 || WIN_LEN < 10 || WIN_HEIGHT < 10)
		return (-1);
	if (argc != 2 || (p = get_map(argv[1])) == NULL)
		return (-1);
	if (!(env = (t_env*)malloc(sizeof(t_env))))
		return (-1);
	if (!(env->mlx = mlx_init()))
		return (-1);
	if (!(env->win = mlx_new_window(env->mlx, WIN_LEN, WIN_HEIGHT, TITLE)))
		return (-1);
	if (!(env->img = new_img(env)))
		return (-1);
	env->p = p;
	color_map(env);
	map_center(env);
	if (get_max(env, env->p) == 0)
		return (0);
	center_points(env);
	if (draw_map(p, env) == -1)
		return (-1);//fermer la fenetre et exit
	mlx_key_hook(env->win, event, env);
	mlx_expose_hook(env->win, print_img, env);
	mlx_loop(env->mlx);
	return (0);
}
