/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_queue.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:38:11 by jbadaire          #+#    #+#             */
/*   Updated: 2023/11/23 09:26:59 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minitalk.h"

t_bitqueue	*init_sigqueue(void)
{
	t_bitqueue	*queue;

	queue = malloc(sizeof(t_bitqueue));
	if (!queue)
	{
		ft_printf("Error -> \nSorry, queue can't be initialised\n");
		return (NULL);
	}
	return (queue);
}

void	queue_add(int sig, t_bitqueue *queue)
{
	t_bitqueue	*new;

	if (!queue->bit)
	{
		queue->bit = sig;
		return ;
	}
	new = malloc(sizeof(t_bitqueue));
	if (!new)
		return ;
	new->bit = sig;
	new->next = NULL;
	last(queue, new);
}

void	last(t_bitqueue *lst, t_bitqueue *new)
{
	t_bitqueue	*tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	queue_next(t_bitqueue **queue)
{
	t_bitqueue			*copy;
	int					y;

	if (*queue == NULL)
		return (666);
	copy = *queue;
	y = (*queue)->bit;
	*queue = copy->next;
	return (y);
}

void	free_queue(t_bitqueue *queue)
{
	t_bitqueue	*copy;

	while (queue != NULL)
	{
		copy = queue;
		queue = queue->next;
		free(copy);
	}
}
