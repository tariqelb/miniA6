/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 18:21:10 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/05/03 14:14:43 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"

char	*ft_echo_q(char *exp)
{
	int	flag;
	int	i;
	int	j;

	i = 0;
	j = 0;
	flag = 0;
	while (exp[i])
	{
		if (exp[i] == 39)
			flag++;
		if (exp[i] == 34 && !(flag % 2))
		{
			i++;
			while (exp[i] != 34 && exp[i])
				exp[j++] = exp[i++];
			i++;
		}
		else
			exp[j++] = exp[i++];
	}
	exp[j] = 0;
	return (exp);
}

void	ft_echo_util_two(t_mini *line, t_echo ech, g_built *built)
{
	char	*exp;
	char	**opt;
	int		k;
	int		j;

	exp = NULL;
	opt = line[0].opt_args;
	j = ech.newline;
	if (line[0].opt_args && ft_strcmp(line[0].opt_args[0], "-") == 0)
		j = 1;
	while (opt && opt[j])
	{
		k = 0;
		while (k < ech.i)
		{
			exp = ft_echo_q(ft_expand(line, &exp, opt[j], built));
			write(ech.fds[k], exp, ft_strlen(exp));
			if (opt[j + 1])
				write(ech.fds[k], " ", 1);
			k++;
			free(exp);
		}
		j++;
	}
	ft_newline(ech.i, ech.newline, ech.fds);
}

int	ft_check_echo_files(t_mini *line)
{
	int		stt;

	stt = ft_here_doc(line);
	if (line[0].error != NULL)
	{
		write(2, line[0].error, ft_strlen(line[0].error));
		return (write(2, "\n", 1));
	}
	stt = ft_file_in(line);
	if (stt)
		return (1);
	stt = ft_file_out(line);
	if (stt)
		return (1);
	return (0);
}

int	ft_echo(t_mini *line, g_built *built)
{
	t_echo	ech;

	ech.i = 0;
	if (ft_check_echo_files(line))
		return (1);
	while (line[0].std_out && line[0].std_out[ech.i] != NULL)
		ech.i++;
	ech.newline = ft_valide_opt(line[0]);
	if (ech.i != 0)
	{
		ech.fds = (int *) malloc(sizeof(int) * ech.i);
		ech.fds = ft_open_files(line, ech.fds, ech.i);
	}
	else
	{
		ech.fds = (int *) malloc(sizeof(int) * 1);
		ech.fds[0] = 1;
		ech.i = 1;
	}
	ft_echo_util(line, ech, built);
	free(ech.fds);
	return (0);
}
