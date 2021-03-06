/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis_V.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 01:21:09 by mabdelou          #+#    #+#             */
/*   Updated: 2022/05/01 22:18:48 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../execution/exe_header.h"
#include "../parssing/minishell.h"

char	*ft_strdup_qoute(const char *s1, int num_of_qoute)
{
	char	*dest;
	int		len;
	int a;

	(void)	num_of_qoute;
	dest = NULL;
	len = -1;
	while(s1[++len])
		;
	dest = (char *) malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	len = -1;
	a = -1;
	while (s1[++len] != '\0')
		if (s1[len] != 34 && s1[len] != 39)
			dest[++a] = s1[len];
	dest[++a] = '\0';
	return (dest);
}


int ft_check_qoute(t_mini *data, int b, int loop)
{
	int a;
	int num_of_qoute;
	char *change_opt_args;

	a = -1;
	num_of_qoute = 0;
	while(data[loop].opt_args[b][++a] != '\0'
		&& data[loop].opt_args[b][a] != '=')
		if (data[loop].opt_args[b][a] == 34 || data[loop].opt_args[b][a] == 39)
			++num_of_qoute;
	change_opt_args = ft_strdup_qoute(data[loop].opt_args[b],num_of_qoute);
	free(data[loop].opt_args[b]);
	data[loop].opt_args[b] = change_opt_args;
	return (num_of_qoute);
}

int	ft_check_var(t_mini *data, int b, int loop)
{
	int	a;
	int num_of_qoute;

	num_of_qoute = ft_check_qoute(data, b, loop);
	// printf("%d\n",num_of_qoute);
	// if (num_of_qoute % 2 == 1)
	// 	return (0);
	a = -1;
	while (data[loop].opt_args[b][++a])
	{
		if (!ft_isalpha(data[loop].opt_args[b][a], a))
		{
			if (data[loop].opt_args[b][a] == '=')
				return (1);
			return (0);
		}
	}
	return (1);
}

void	ft_change_shlvl(t_mini *data, g_built *built)
{
	static int	a = -1;
	char		lvl[2];
	char		*join;

	(void) data;
	if (a == -1)
	{
		while (built->envp[++a])
		{
			if (!ft_strncmp(built->envp[a], "SHLVL=", 6))
			{
				lvl[0] = (built->envp[a][6] + 1);
				lvl[1] = 0;
				free(built->envp[a]);
				join = ft_strjoin("SHLVL=", lvl);
				built->envp[a] = ft_strdup(join);
				// free(join);
			}
		}
		a = -1;
		while (built->export[++a])
		{
			if (!ft_strncmp(built->export[a], "SHLVL=", 6))
			{
				free(built->export[a]);
				built->export[a] = ft_strdup(join);
				free(join);
			}
		}
	}
}
