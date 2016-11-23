/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 05:27:48 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/23 05:30:05 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		while (str[x] != NULL)
		{
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
