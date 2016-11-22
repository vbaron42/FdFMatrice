/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 16:50:50 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/23 00:14:38 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h> //utile ? a mettre dans le .h ?

void		ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	exit(1);
}

t_point			*ft_lstadd_p(t_point *p, int x, char *str, int z)
{
	t_point		*newp;
	t_point		*tmp;

	if ((newp = (t_point *)malloc(sizeof(t_point))) == NULL)
		ft_error("Malloc error\n");
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
		ft_error("Malloc error\n");
	z = 0;
	while ((x = get_next_line(fd, &line)) != 0)
	{
		if (x == -1)
			ft_error("Get_next_line return -1\n");
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

	if (!(ft_strstr(file, ".fdf")))
		ft_error("Usage : ./fdf file.fdf <-\n");
	if ((fd = open(file, O_RDONLY)) == -1)
		ft_error("The file can't be open\n");
	p = fill_p(fd);
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

int				main(int argc, char **argv)
{
	t_point		*p;
	t_env		*env;
	void		*mlx;
	void		*win;

	if (WIN_LEN > 2500 || WIN_HEIGHT > 1500 || WIN_LEN < 10 || WIN_HEIGHT < 10)
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
	color_map(env);
	map_center(env);
	get_max(env, env->p);
	center_points(env);
	draw_map(p, env);
	mlx_key_hook(env->win, event, env);
	mlx_expose_hook(env->win, print_img, env);
	mlx_loop(env->mlx);
	return (0);
}
