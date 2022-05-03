/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 20:57:29 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/05/03 13:11:16 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free_tab(char **str, char *arg1, char *arg2)
{
	int	i;

	if (str == NULL)
		return (str);
	if (str != NULL)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			i++;
		}
		free(str);
	}
	if (arg1 != NULL)
		free(arg1);
	if (arg2 != NULL)
		free(arg2);
	str = NULL;
	return (str);
}

void	ft_free_util(t_mini *line, int i)
{
	ft_free_tab(line[i].opt_args, NULL, NULL);
	ft_free_tab(line[i].std_in, NULL, NULL);
	ft_free_tab(line[i].std_out, NULL, NULL);
	ft_free_tab(line[i].trunc, NULL, NULL);
	ft_free_tab(line[i].limiter, NULL, NULL);
	ft_free_tab(line[i].order, NULL, NULL);
	ft_free_tab(line[i].orlim, NULL, NULL);
	ft_free_tab(line[i].f_ord, NULL, NULL);
	ft_free_tab(line[i].f_o_d, NULL, NULL);
}

void	ft_free_cmd(t_mini *line)
{
	int	i;

	i = 0;
	if (line == NULL)
		return ;
	while (line[i].fcl != NULL)
	{
		if (line[i].f_cmd != NULL)
			free(line[i].f_cmd);
		if (line[i].cmd_path != NULL)
			free(line[i].cmd_path);
		if (line[i].cmd != NULL)
			free(line[i].cmd);
		ft_free_util(line, i);
		i++;
	}
	if (line[0].error != NULL)
		free(line[0].error);
	free(line[0].fcl);
	free(line);
}
