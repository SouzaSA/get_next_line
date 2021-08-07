/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sde-alva <sde-alva@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:36:56 by sde-alva          #+#    #+#             */
/*   Updated: 2021/08/07 20:35:41 by sde-alva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_fd_list	*ft_get_fd(t_fd_list **fd_list, int fd);
t_fd_list	*ft_add_fd(t_fd_list **fd_list, int fd);
void		ft_del_list(t_fd_list **fd_list, int fd);

char	*get_next_line(int fd)
{
	static t_fd_list	*desc_list = NULL;
	t_fd_list			*fd_node;
	char				*str;

	str = NULL;
	if (fd >= 0 && read(fd, str, 0) == 0)
	{
		fd_node = ft_get_fd(&desc_list, fd);
		if (fd_node)
		{
			ft_push_line(fd, &(fd_node->str_buff));
			str = ft_pop_line(&(fd_node->str_buff));
		}
	}
	if (!str && fd_node)
		ft_del_list(&desc_list, fd);
	return (str);
}

t_fd_list	*ft_get_fd(t_fd_list **fd_list, int fd)
{
	t_fd_list	*list;

	list = *fd_list;
	while (list && list->fd != fd)
		list = list->next;
	if (!*fd_list)
	{
		*fd_list = ft_add_fd(&list, fd);
		list = *fd_list;
	}
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
	return (*fd_list);
}

void	ft_del_list(t_fd_list **fd_list, int fd)
{
	int			is_clean;
	t_fd_list	*list;
	t_fd_list	*node;

	is_clean = 1;
	if (*fd_list)
	{
		node = ft_get_fd(fd_list, fd);
		if (node->str_buff)
			free(node->str_buff);
		node->str_buff = NULL;
		list = *fd_list;
		while (list)
		{
			if (list->str_buff)
				is_clean = 0;
			list = list->next;
		}
		list = *fd_list;
		if (is_clean && list)
		{
			list = (*fd_list)->next;
			free(*fd_list);
			*fd_list = list;
		}
	}
}
