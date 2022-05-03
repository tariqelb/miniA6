/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis_I.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:47:55 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/23 14:47:57 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../execution/exe_header.h"
#include "../parssing/minishell.h"

void	ft_exelen(t_mini *data, g_built *built, int loop)
{
	int	a;

	a = 0;
	if (built->export == NULL)
		while (data[loop].env[a])
			++a;
	else
		while (built->export[a] && a < built->num_of_strings)
			++a;
	built->num_of_strings = a;
	return ;
}

void	ft_exportdup(t_mini *data, g_built *built, int loop)
{
	int	a;

	ft_exelen(data, built, loop);
	built->export = malloc(sizeof(char *) * built->num_of_strings + 1);
	if (!built->export)
		return ;
	a = -1;
	while (data[loop].env[++a] && a < built->num_of_strings)
		built->export[a] = ft_strdup(data[loop].env[a]);
	built->export[a] = NULL;
	return ;
}

int	ft_check_expert_before_rm(t_mini *data, g_built *built, int b, int loop)
{
	int	a;

	a = -1;
	while (built->export[++a] && a < built->num_of_strings)
	{
		if (ft_strncmp_built(built->export[a], data[loop].opt_args[b],
				ft_strlen_to(built->export[a], '=')) == 0)
		{
			if (ft_strlen_to(built->export[a], '=')
				== ft_strlen(data[loop].opt_args[b]))
				return (a);
		}
	}
	return (a);
}

int	ft_calc_args(t_mini *data, int loop)
{
	int	a;

	a = -1;
	while (data[loop].opt_args[++a])
		;
	return (a);
}

void	ft_print_export(t_mini *data, g_built *built, int loop)
{
	int	a;

	(void) data;
	a = -1;
	ft_exelen(data, built, loop);
	if (built->export)
		while (built->export[++a] && a < built->num_of_strings)
			printf("declare -x %s\n", built->export[a]);
	return ;
}
