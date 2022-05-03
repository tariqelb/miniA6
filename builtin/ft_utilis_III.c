/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis_III.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:52:30 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/23 14:52:32 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../execution/exe_header.h"
#include "../parssing/minishell.h"

char	**ft_addvar(t_mini *data, g_built *built, int b, int loop)
{
	int		a;
	char	**new_export;

	(void) data;
	ft_exelen(data, built, loop);
	new_export = malloc(sizeof(char *) * (built->num_of_strings + 2));
	if (!new_export)
		return (NULL);
	ft_bzero(new_export, built->num_of_strings + 1);
	a = -1;
	while (built->export[++a] && a < built->num_of_strings)
		new_export[a] = ft_strdup(built->export[a]);
	new_export[a] = ft_strdup(data[loop].opt_args[b]);
	new_export[a + 1] = NULL;
	a = -1;
	while (built->export[++a] && a < built->num_of_strings)
		free(built->export[a]);
	free(built->export);
	built->num_of_strings = a + 1;
	return (new_export);
}

char	**ft_delvar(t_mini *data, g_built *built, int b, int loop)
{
	int		a;
	int		c;
	char	**new_export;

	(void) data;
	new_export = malloc(sizeof(char *) * (built->num_of_strings));
	if (!new_export)
		return (NULL);
	ft_bzero(new_export, built->num_of_strings);
	a = -1;
	c = -1;
	while (built->export[++a] && a < built->num_of_strings)
	{
		if (ft_strncmp_built(built->export[a], data[loop].opt_args[b],
				ft_strlen_to(built->export[a], '=')) != 0)
			new_export[++c] = ft_strdup(built->export[a]);
	}
	new_export[c + 1] = NULL;
	a = -1;
	while (built->export[++a] && a < built->num_of_strings)
		free(built->export[a]);
	free(built->export);
	built->num_of_strings = a - 1;
	return (new_export);
}

void	ft_sort_export_v2(t_mini *data, g_built *built, int a, int b)
{
	(void) data;
	if (ft_strncmp_exe(built->export[a], built->export[b]) > 0)
	{
		built->swap = ft_strdup(built->export[a]);
		if (built->export[a])
			free(built->export[a]);
		built->export[a] = ft_strdup(built->export[b]);
		if (built->export[b])
			free(built->export[b]);
		built->export[b] = ft_strdup(built->swap);
		free(built->swap);
	}
}

void	ft_sort_export(t_mini *data, g_built *built)
{
	int	a;
	int	b;

	(void) data;
	a = -1;
	while (++a < built->num_of_strings)
	{
		b = a;
		while (++b < built->num_of_strings)
		{
			if (ft_strncmp_exe(built->export[a], built->export[b]) > 0)
				ft_sort_export_v2(data, built, a, b);
		}
	}
}

void	ft_check_export(t_mini *data, g_built *built, int b, int loop)
{
	int	a;
	int	size;

	a = -1;
	size = ft_iseagal(data[loop].opt_args[b]);
	ft_exelen(data, built, loop);
	while (built->export[++a] && a < built->num_of_strings)
	{
		if (size != 0)
		{
			if (ft_strncmp(built->export[a], data[loop].opt_args[b], size) == 0)
				break ;
		}
		else
		{
			if (ft_strncmp(built->export[a], data[loop].opt_args[b],
					ft_strlen_to(data[loop].opt_args[b], '=')) == 0)
				if (ft_strlen_to(built->export[a], '=')
					== ft_strlen(data[loop].opt_args[b]))
					break ;
		}
	}
	built->loop = loop;
	ft_check_export_v2(data, built, a, b);
}
