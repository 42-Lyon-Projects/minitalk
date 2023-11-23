/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 11:56:41 by jbadaire          #+#    #+#             */
/*   Updated: 2023/11/23 09:26:22 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

int	main(int argc, char *argv[])
{
	int					pid;
	t_bitqueue			*queue;

	pid = client_handle_parsing_errors(argc, argv);
	if (pid < 0)
		return (0);
	queue = init_sigqueue();
	if (queue == NULL)
		return (0);
	queue_string(argv[2], queue);
	client_send_queue(pid, queue);
	free_queue(queue);
	return (0);
}

int	client_handle_parsing_errors(int argc, char *argv[])
{
	int	index;
	int	size;
	int	value;

	index = 0;
	if (argc < 2)
		return (ft_printf("Error -> \nPlease enter the server PID,"\
		" and your message\n"), -1);
	size = (int) ft_strlen(argv[1]);
	while (index < size)
	{
		if (!ft_isdigit(argv[1][index]))
			return (ft_printf("Error -> \nSorry, your pid must"\
			" be only number\n"), -2);
		index++;
	}
	value = ft_atoi(argv[1]);
	if (value <= 0)
		return (ft_printf("Error -> \nSorry, your PID is invalid\n"), -3);
	return (value);
}

void	queue_string(char *content, t_bitqueue *queue)
{
	int		index_str;
	int		index_bits;
	char	character;

	index_str = 0;
	while (content[index_str])
	{
		index_bits = 7;
		character = content[index_str];
		while (index_bits >= 0)
		{
			if ((character >> index_bits) & 1)
				queue_add(SIGUSR1, queue);
			else
				queue_add(SIGUSR2, queue);
			index_bits--;
		}
		index_str++;
	}
	index_bits = 8;
	while (index_bits > 0)
	{
		queue_add(SIGUSR2, queue);
		index_bits--;
	}
}

int	client_send_queue(int pid, t_bitqueue *queue)
{
	unsigned long	sig_id;
	t_boolean		sended;
	int				tries;

	sig_id = queue_next(&queue);
	if (sig_id == 666)
	{
		ft_printf("Success -> Message sended !\n");
		return (0);
	}
	sended = kill(pid, (int)sig_id) == 0;
	tries = 0;
	while (!sended && tries++ < 10)
	{
		usleep(10000);
		sended = kill(pid, (int)sig_id) != 0;
	}
	if (!sended)
	{
		ft_printf("Error -> \nSorry i can't send bit.\nClient stop !");
		exit(0);
	}
	usleep(10000);
	client_send_queue(pid, queue);
	return (0);
}
