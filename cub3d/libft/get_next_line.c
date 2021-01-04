/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 16:08:43 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/29 12:41:00 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_fd	*ft_new_elmt_lst(int fd)
{
	t_fd *new;

	if (!(new = ft_calloc(sizeof(t_fd), 1)))
		return (0);
	new->fd = fd;
	new->buff = NULL;
	new->next = 0;
	new->start = 0;
	new->end = 0;
	return (new);
}

static t_fd	*ft_search_fd(t_fd **begin, int fd)
{
	t_fd *lst;
	t_fd *tmp;

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
	t_fd *tmp;

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
	if (!(*line = ft_substr(obj->buff, obj->start, obj->end - obj->start)))
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

int			get_next_line(int fd, char **line)
{
	static t_fd	*begin_lst;
	t_fd		*obj;
	int			res;

	if (line == NULL || fd < 0 || BUFFER_SIZE <= 0)
		return (-1);
	if (!(obj = ft_search_fd(&begin_lst, fd)))
		return (-1);
	while (!obj->buff ||
	obj->buff[(obj->end += ft_strpos(&(obj->buff[obj->end]), '\n'))] != '\n')
	{
		if (!(obj->buff = ft_realloc(obj->buff, BUFFER_SIZE)))
			return (ft_clear_fd(&begin_lst, obj, -1));
		if ((res = read(fd, &(obj->buff[obj->end]), BUFFER_SIZE)) == 0)
			return (ft_new_line(line, obj, &begin_lst, 0));
		if (res == -1)
			return (ft_clear_fd(&begin_lst, obj, -1));
	}
	return (ft_new_line(line, obj, &begin_lst, 1));
}
