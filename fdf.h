/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 01:58:23 by vcohere           #+#    #+#             */
/*   Updated: 2014/12/23 17:52:39 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include "libft/includes/libft.h"

typedef struct		s_3dpos
{
	int				x;
	int				y;
	int				z;
}					t_3dpos;

typedef struct		s_2dpos
{
	int				x;
	int				y;
}					t_2dpos;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	int				*map;
	int				line;
	size_t			size;
}					t_env;

int					start_env(int *tab, int line, int size);
int					start_it(int *tab, int line, int size);
void				trace_seg(t_2dpos p1, t_2dpos p2, t_env *e);
void				trace_map(t_env *env);
t_2dpos				convert_coords(int y, int x, int z);

#endif
