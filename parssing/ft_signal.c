/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:28:12 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/05/01 21:34:09 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_sigint_handler(int sig)
{
	(void) sig;
	built.end_state = 33280;
	if (built.flag == 0)
	{
		printf("Prompt $\n");
		rl_on_new_line();
		rl_redisplay();
	}
	else
	{
		printf("Prompt $\n");
	}
}

void	ft_sigquit_handler(int sig)
{
	(void) sig;
	printf("exit\n");
	exit(0);
}

void	ft_sig_handler(int sig)
{
	(void) sig;
}

void	ft_init_sig(g_built *built, int ac, char **av)
{
	(void) ac;
	(void) av;
	built->export = NULL;
	built->envp = NULL;
	signal(SIGINT, ft_sigint_handler);
	signal(SIGQUIT, ft_sig_handler);
}
