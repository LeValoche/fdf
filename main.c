/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/12/17 01:49:38 by vcohere           #+#    #+#             */
/*   Updated: 2014/12/17 01:49:39 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			ft_dbtablen(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int			check_errors(int fd)
{
	int		line;
	int		size;
	char	*str;

	line = 0;
	size = 0;
	while (get_next_line(fd, &str) > 0)
	{
		if (line == 0)
			line = ft_dbtablen(ft_strsplit(str, ' '));
		if (ft_dbtablen(ft_strsplit(str, ' ')) != line)
			return (-1);
		size += line;
	}
	return (size);
}

int			line_size(int fd)
{
	char	*str;

	get_next_line(fd, &str);
	return (ft_dbtablen(ft_strsplit(str, ' ')));
}

int			*get_map(int fd, int size)
{
	int		*map;
	int		i;
	char	*str;
	char	**tab;

	i = 1;
	if (!(map = (int *)malloc(sizeof(int) * size + 1)))
		return (NULL);
	while (get_next_line(fd, &str))
	{
		tab = ft_strsplit(str, ' ');
		if (i == 1)
			map[0] = ft_dbtablen(tab);
		while (*tab)
		{
			map[i] = ft_atoi((const char *)*tab);
			i++;
			tab++;
		}
	}
	return (map);
}

int			main(int ac, char **av)
{
	int		*map;
	int		size;
	int		line;
	int		fd;

	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (0);								// Error
	if ((size = check_errors(fd)) == -1)
		return (0);								// Error
	close(fd);
	fd = open(av[1], O_RDONLY);
	map = get_map(fd, size);
	line = *map++;
	start_env(map, line, size);
	return (0);
}
