/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis_IV.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:33:25 by mabdelou          #+#    #+#             */
/*   Updated: 2022/05/01 22:40:23 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../execution/exe_header.h"
#include "../parssing/minishell.h"

void	ft_envlen(t_mini *data, g_built *built, int loop)
{
	int	a;
	int	b;

	a = -1;
	b = 0;
	if (built->export == NULL)
	{
		while (data[loop].env[++a])
			;
		built->num_of_env_strings = a;
		return ;
	}
	else
	{
		while (built->export[++a] && a < built->num_of_strings)
			if (ft_iseagal(built->export[a]))
				++b;
		built->num_of_env_strings = b;
		return ;
	}
}

void	ft_free_env(t_mini *data, g_built *built)
{
	int		a;

	(void) data;
	a = -1;
	if (built->envp != NULL)
		while (built->envp[++a] && a < built->num_of_env_strings)
			free(built->envp[a]);
	free(built->envp);
	return ;
}

void	ft_envdup(t_mini *data, g_built *built, int loop)
{
	int	a;
	int	b;

	ft_free_env(data, built);
	ft_envlen(data, built, loop);
	built->envp = malloc(sizeof(char *) * built->num_of_env_strings + 1);
	if (!built->envp)
		return ;
	a = -1;
	b = 0;
	if (built->export != NULL)
	{
		while (built->export[++a] && b < built->num_of_env_strings)
			if (ft_iseagal(built->export[a]))
				built->envp[b++] = ft_strdup(built->export[a]);
			built->envp[b++] = NULL;
	}
	else if (built->export == NULL)
	{
		ft_exportdup(data, built, loop);
		while (built->export[++a] && b < built->num_of_env_strings)
			built->envp[b++] = ft_strdup(built->export[a]);
		built->envp[a++] = NULL;
	}
	ft_envlen(data, built, loop);
}

void	ft_print_env(t_mini *data, g_built *built, int loop)
{
	int	a;

	(void) data;
	a = -1;
	ft_envlen(data, built, loop);
	if (built->envp)
		while (built->envp[++a] && a < built->num_of_env_strings)
			printf("%s\n", built->envp[a]);
	return ;
}

void	ft_check_export_v2(t_mini *data, g_built *built, int a, int b)
{
	int	size;
	int	loop;

	loop = built->loop;
	size = ft_iseagal(data[loop].opt_args[b]);
	if (a == built->num_of_strings && size != 0)
		built->export = ft_addvar(data, built, b, loop);
	else if (a == built->num_of_strings && size == 0)
		built->export = ft_addvar(data, built, b, loop);
	else if (a != built->num_of_strings && size != 0)
	{
		free(built->export[a]);
		built->export[a] = strdup(data[loop].opt_args[b]);
	}
	else if (a != built->num_of_strings && size == 0)
		return ;
}
