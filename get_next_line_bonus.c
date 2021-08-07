/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-alva <sde-alva@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:36:56 by sde-alva          #+#    #+#             */
/*   Updated: 2021/08/06 23:13:55 by sde-alva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fd_list	*ft_get_fd(t_fd_list **fd_list, int fd);
t_fd_list	*ft_add_fd(t_fd_list **fd_list, int fd);
void		ft_del_list(t_fd_list **fd_list);

char	*get_next_line(int fd)
{
	static t_fd_list	*desc_list = NULL;
	char				**to_read;
	char				*str;

	str = NULL;
	*to_read = NULL;
	if (fd >= 0 && read(fd, str, 0) == 0)
	{
		desc_list = ft_get_fd(&desc_list, fd);
		if (!desc_list)
			desc_list = ft_add_fd(&desc_list, fd);
		if (desc_list)
		{
			to_read = &(desc_list->str_buff);
			ft_push_line(fd, to_read);
			if (to_read)
				str = ft_pop_line(to_read);
		}
	}
	if (!str)
	{
		free(*to_read);
		*to_read = NULL;
		ft_del_list(&desc_list);
	}
	return (str);
}

t_fd_list	*ft_get_fd(t_fd_list **fd_list, int fd)
{
	t_fd_list	*list;

	list = *fd_list;
	while (list && list->fd != fd)
		list = list->next;
	return (list);
}

t_fd_list	*ft_add_fd(t_fd_list **fd_list, int fd)
{
	t_fd_list	*list;
	t_fd_list	*new_node;

	new_node = (t_fd_list *)malloc(sizeof(t_fd_list));
	if (new_node)
	{
		new_node->fd = fd;
		new_node->str_buff = NULL;
		new_node->next = NULL;
		list = *fd_list;
		if (list)
		{
			while (list->next)
				list = list->next;
			list->next = new_node;
		}
		else
		{
			*fd_list = new_node;
		}
	}
	return (new_node);
}

void	ft_del_list(t_fd_list **fd_list)
{
	int			is_clean;
	t_fd_list	*list;

	is_clean = 1;
	if (*fd_list)
	{
		list = *fd_list;
		while (list)
		{
			if (list->str_buff)
				is_clean = 0;
			list = list->next;
		}
		list = *fd_list;
		if (list && is_clean)
		{
			list = (*fd_list)->next;
			free(*fd_list);
			*fd_list = list;
		}
	}
}
