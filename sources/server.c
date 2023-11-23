/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbadaire <jbadaire@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 19:50:18 by jbadaire          #+#    #+#             */
/*   Updated: 2023/11/23 10:36:07 by jbadaire         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minitalk.h"

char	*g_str = NULL;

void	print_minitalk(void)
{
	ft_printf("        _       _ _____      _ _            "\
	"  __                          \n"\
	"  /\\/\\ (_)_ __ (_)__   \\__ _| | | __         "\
	"/ _\\ ___ _ ____   _____ _ __ \n"\
	" /    \\| | '_ \\| | / /\\/ _` | | |/ /  _____  "\
	"\\ \\ / _ \\ '__\\ \\ / / _ \\ '__|\n"\
	"/ /\\/\\ \\ | | | | |/ / | (_| | |   <  |_____| "\
	"_\\ \\  __/ |   \\ V /  __/ |   \n"\
	"\\/    \\/_|_| |_|_|\\/   \\__,_|_|_|\\_\\      "\
	"   \\__/\\___|_|    \\_/ \\___|_|   \n\n");
}

void	server_get_char(int signum, siginfo_t *info, void *context)
{
	static char	character = 0;
	static int	bits = 0;
	char		*tmp;

	(void) context;
	(void) info;
	if (!g_str)
		g_str = ft_strdup("");
	if (signum == SIGUSR1)
		character |= (1 << (7 - bits));
	if (++bits == 8 && character == '\0')
		print_string(&bits, &character);
	else if (bits == 8)
	{
		tmp = ft_strjoin(g_str, &character);
		free(g_str);
		g_str = tmp;
		character = 0;
		bits = 0;
	}
	usleep(10000);
}

void	print_string(int *bits, char *character)
{
	ft_printf("String received: %s\n", g_str);
	free(g_str);
	g_str = NULL;
	*bits = 0;
	*character = 0;
}

int	main(void)
{
	struct sigaction	siga;

	print_minitalk();
	g_str = NULL;
	ft_printf("PID: %d\nMinitalk is waiting...\n\n", getpid());
	sigemptyset(&siga.sa_mask);
	siga.sa_flags = SA_RESTART;
	siga.sa_sigaction = server_get_char;
	if (sigaction(SIGUSR1, &siga, NULL) == -1 || \
	sigaction(SIGUSR2, &siga, NULL) == -1)
	{
		ft_printf("Error ->\n Sigaction error, exit !");
		return (0);
	}
	while (1)
		pause();
}
