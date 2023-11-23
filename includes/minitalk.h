/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:03:06 by jbadaire          #+#    #+#             */
/*   Updated: 2023/11/23 09:35:51 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "../dependencies/libft/libft.h"
# include <signal.h>

// ** QUEUE SYSTEM **//
typedef struct s_bitqueue
{
	int					bit;
	struct s_bitqueue	*next;
}	t_bitqueue;
t_bitqueue		*init_sigqueue(void);
void			queue_add(int sig, t_bitqueue *queue);
int				queue_next(t_bitqueue **queue);
void			free_queue(t_bitqueue *queue);
void			last(t_bitqueue *lst, t_bitqueue *new);

// ** CLIENT PART ** //
int				client_handle_parsing_errors(int argc, char *argv[]);
void			queue_string(char *content, t_bitqueue *queue);
int				client_send_queue(int pid, t_bitqueue *queue);

// ** SERVER PART ** //
void			server_get_char(int signum, siginfo_t *info, void *context);
void			print_string(int *bits, char *character);

#endif