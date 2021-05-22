/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:08:43 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:58:57 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_fd	*ft_new_elmt_lst(int fd)
{
	t_fd	*new;

	new = ft_calloc(sizeof(t_fd), 1);
	if (!new)
		return (0);
	ft_bzero(new, sizeof(t_fd));
	new->fd = fd;
	return (new);
}

static t_fd	*ft_search_fd(t_fd **begin, int fd)
{
	t_fd	*lst;
	t_fd	*tmp;

	lst = (*begin);
	tmp = lst;
	if (lst)
	{
		while (lst)
		{
			if (lst->fd == fd)
				return (lst);
			tmp = lst;
			lst = lst->next;
		}
		tmp->next = ft_new_elmt_lst(fd);
		return (tmp->next);
	}
	else
		*begin = ft_new_elmt_lst(fd);
	return (*begin);
}

static int	ft_clear_fd(t_fd **begin, t_fd *lst, int value)
{
	t_fd	*tmp;

	tmp = (*begin);
	if (tmp->fd == lst->fd)
		(*begin) = lst->next;
	else
	{
		while (tmp->next->fd != lst->fd)
			tmp = tmp->next;
		tmp->next = lst->next;
	}
	if (lst->buff)
	{
		free(lst->buff);
		lst->buff = NULL;
	}
	if (lst)
	{
		free(lst);
		lst = NULL;
	}
	return (value);
}

static int	ft_new_line(char **line, t_fd *obj, t_fd **begin, int value)
{
	*line = ft_substr(obj->buff, obj->start, obj->end - obj->start);
	if (!(*line))
		value = -1;
	obj->end++;
	obj->start = obj->end;
	if (obj->buff && !(obj->buff[obj->start]))
	{
		obj->start = 0;
		obj->end = 0;
		free(obj->buff);
		obj->buff = NULL;
	}
	if (value != 1)
		return (ft_clear_fd(begin, obj, value));
	return (value);
}

int	get_next_line(int fd, char **line)
{
	static t_fd	*begin_lst;
	t_fd		*obj;
	int			res;

	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	obj = ft_search_fd(&begin_lst, fd);
	if (!obj)
		return (-1);
	obj->end += ft_strpos(&(obj->buff[obj->end]), '\n');
	while (!obj->buff || obj->buff[obj->end] != '\n')
	{
		obj->buff = ft_realloc(obj->buff, BUFFER_SIZE);
		if (!obj->buff)
			return (ft_clear_fd(&begin_lst, obj, -1));
		res = read(fd, &(obj->buff[obj->end]), BUFFER_SIZE);
		if (!res)
			return (ft_new_line(line, obj, &begin_lst, 0));
		else if (res == -1)
			return (ft_clear_fd(&begin_lst, obj, -1));
		obj->end += ft_strpos(&(obj->buff[obj->end]), '\n');
	}
	return (ft_new_line(line, obj, &begin_lst, 1));
}
