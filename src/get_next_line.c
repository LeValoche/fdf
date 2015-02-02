/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcohere <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/29 00:56:15 by vcohere           #+#    #+#             */
/*   Updated: 2014/12/02 18:50:20 by vcohere          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int				ft_cpybuf(char *str, char **line, char *br, t_buf buf)
{
	int					i;

	*line = br ? malloc(br - str + 1) : malloc(buf.read + 1);
	if (!*line)
		return (-1);
	i = 0;
	while (*str)
	{
		if (*str == '\n')
			break ;
		(*line)[i] = *str++;
		i++;
	}
	(*line)[i] = 0;
	return (i);
}

int						get_next_line(int fd, char **line)
{
	static t_buf		save[MAX_FILES];
	char				*buffer;
	char				*tmp2;
	char				*br;
	ssize_t				ret;

	X;
	if (!GETBUF(fd))
		GETBUF(fd) = ft_memalloc(1);
	while (!(br = ft_strchr(GETOFFSET(fd), '\n'))
		&& (ret = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		GETREAD(fd) += ret;
		buffer[ret] = '\0';
		SWAP(GETBUF(fd), ft_strjoin(GETOFFSET(fd), buffer), tmp2);
		GETREADED(fd) = 0;
	}
	if (ft_strlen(GETOFFSET(fd)) == 0 && ret == 0)
		OHOHOHAHAHAH;
	if (GETREAD(fd) == -1 || ret < 0
		|| (ret = ft_cpybuf(GETOFFSET(fd), line, br, save[fd])) == -1)
		return (-1);
	GETREADED(fd) += (GETOFFSET(fd)[ret] != 0) ? ret + 1 : ret;
	GETREAD(fd) -= (GETOFFSET(fd)[ret] != 0) ? ret + 1 : ret;
	return (1);
}