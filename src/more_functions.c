/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 03:24:18 by vcohere           #+#    #+#             */
/*   Updated: 2014/12/17 03:24:19 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int					expose_handler(void *param)
{
	t_env			**env;

	env = (t_env **)param;
	trace_map(*env);
	return (0);
}

int					key_handler(int keycode, void *param)
{
	(void)param;
	if (keycode == 0xff1b)
		exit(0);
	return (0);
}

int					start_env(int *tab, int line, int size)
{
	t_env			*env;

	env = (t_env *)malloc(sizeof(t_env));
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, 1200, 800, "Fil de FERRRR");
	env->map = tab;
	env->line = line;
	env->size = size;
	mlx_expose_hook(env->win, expose_handler, &env);
	mlx_key_hook(env->win, key_handler, &env);
	mlx_loop(env->mlx);
	trace_map(env);
	return (0);
}

t_2dpos				convert_coords(int y, int x, int z)
{
	t_2dpos			pos;

	pos.y = 500 + 30 * x - 20 * y;
	pos.x = 100 + 35 * y + 20 * x - 3 * z;
	return (pos);
}

int					choose_color(int y)
{
	(void)y;
	return (0xFE2EF7);
}

void				trace_map(t_env *env)
{
	int				i;

	i = 0;
	while ((unsigned int)i < env->size)
	{
		if (i % env->line != env->line - 1)
			trace_seg(
				convert_coords(i % env->line, i / env->line, env->map[i]), 
				convert_coords(i % env->line + 1, i / env->line, env->map[i + 1]),
				env, choose_color(env->map[i]));
		if (i / env->line < (int)env->size / env->line - 1)
			trace_seg(
				convert_coords(i % env->line, i / env->line, env->map[i]), 
				convert_coords(i % env->line, i / env->line + 1, env->map[i + env->line]),
				env, choose_color(env->map[i]));
		i++;
	}
}

void				trace_seg(t_2dpos p1, t_2dpos p2, t_env *e, int color)
{
	float			p[2];
	float			dx;
	float			dy;
	float			len;
	int				i;

	i = 0;
	if (abs(p2.x - p1.x) >= abs(p2.y - p1.y))
		len = abs(p2.x - p1.x);
	else
		len = abs(p2.y - p1.y);
	dx = (p2.x - p1.x) / len;
	dy = (p2.y - p1.y) / len;
	p[0] = p1.x + 0.5;
	p[1] = p1.y + 0.5;
	while (i <= len)
	{
		mlx_pixel_put(e->mlx, e->win, p[0], p[1], color);
		p[0] += dx;
		p[1] += dy;
		i++;
	}
}
