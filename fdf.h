/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbaron <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/01 22:43:45 by vbaron            #+#    #+#             */
/*   Updated: 2016/11/22 18:07:27 by vbaron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/libft.h"
# include <mlx.h>
# include <math.h>
# define TILE_WIDTH 60
# define TILE_HEIGHT 40
# define P_HEIGHT 1
# define WIN_LEN 900
# define WIN_HEIGHT 950
# define ROT_Y_POW 3.14159265358979323846 / 64
# define SPEED 20
# define SCALE_POWER 0.2

typedef struct		s_matrice
{
	double			a;
	double			b;
	double			c;
	double			d;
	double			e;
	double			f;
	double			g;
	double			h;
	double			i;
	double			j;
	double			k;
	double			l;
	double			m;
	double			n;
	double			o;
	double			p;
}					t_matrice;
/*
typedef struct		s_tab//inutil ?
{
	int				x;
	int				y;
	int				z;
	int				w;
}					t_tab;
*/
typedef struct		s_point
{
	double			x;
	double			y;
	double			z;
	int				c;
	void			*next;
}					t_point;

typedef struct		s_line_data
{
	int				dx;
	int				dy;
	int				ix;
	int				iy;
	int				err;
	int				e;
}					t_line_data;

typedef struct		s_img
{
	void			*ptr;
	int				bpp;
	int				line_size;
	int				endian;
	char			*pxl_byt;
}					t_img;

typedef struct		s_env
{
	int				rl;
	int				ud;
	int				scale;
	int				xmax;//		a enlever du .h et a integrer
	int				ymax;//		dans une fonction
	int				zmax;//		pour trouver scale
	t_point			center;
	void			*mlx;
	void			*win;
	t_img			*img;
//	t_tab			**tab;
	t_point			*p;
	int				error;
}					t_env;

void				m_rot_y(t_env *env, double x);
void				map_center(t_env *env);
//void				matricialisation(t_env *env, t_point *p, t_matrice *m);
void				m_scale(t_env *env, double s);
void				m_rlud(t_env *env, double x, double y);
t_point				*matricialisation(t_env *env, t_point *p, t_matrice *m);
//t_point				*m_scale(t_env *env, double s);
//t_point				*m_rlud(t_env *env, double x, double y);
void				matrice(t_env *env, t_matrice *m);
int					event(int keycode, t_env *env);
t_img				*new_img(t_env *env);
int					print_img(t_env *env);
t_point				*get_map(char *file);
t_point				ortho_to_iso(t_point p, t_env env);
int					draw_map(t_point *p, t_env *env);
#endif
