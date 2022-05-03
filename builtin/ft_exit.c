/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:50:49 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/05/01 22:19:58 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"

int	ft_exit_util(t_mini *line, g_built *built)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (line[0].opt_args[0][i])
	{
		if (line[0].opt_args[0][i] < 48 || line[0].opt_args[0][i] > 57)
			flag = 1;
		i++;
	}
	if (flag)
	{
		write(2, "exit\n", 5);
		write(2, "bash: exit: ", 12);
		write(2, line[0].opt_args[0], ft_strlen(line[0].opt_args[0]));
		write(2, "numeric argument required\n", 26);
		built->end_state = 1;
		return (1);
	}
	flag = ft_atoi(line[0].opt_args[0]);
	write(2, "exit\n", 5);
	built->end_state = flag;
	exit(flag);
}

int	ft_exit(t_mini *line, g_built *built)
{
	int	len;
	int	stt;

	len = 0;
	stt = ft_here_doc(line);
	if (line[0].error != NULL)
	{
		write(2, line[0].error, ft_strlen(line[0].error));
		return (write(2, "\n", 1));
	}
	if (ft_file_in(line) || ft_file_out(line))
		return (1);
	while (line[0].opt_args && line[0].opt_args[len])
		len++;
	if (len == 0)
	{
		write(2, "exit\n", 5);
		built->end_state = 0;
		exit(0);
	}
	else if (len > 1)
		return (write(2, "exit\nbash: exit: too many arguments\n", 36));
	if (ft_exit_util(line, built))
		return (1);
	return (0);
}
