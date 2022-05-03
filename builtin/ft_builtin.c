/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/23 14:21:40 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/23 14:21:45 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../execution/exe_header.h"
#include "../parssing/minishell.h"

int	ft_unset_v1(t_mini *data, g_built *built, int loop)
{
	int	a;

	a = -1;
	if (built->export == NULL)
		ft_exportdup(data, built, loop);
	ft_sort_export(data, built);
	while (++a < ft_calc_args(data, loop))
	{
		if (ft_check_var(data, a, loop)
			&& !ft_iseagal(data[loop].opt_args[a]))
		{
			if (ft_check_expert_before_rm(data, built, a, loop)
				!= built->num_of_strings)
				built->export = ft_delvar(data, built, a, loop);
		}
		else
		{
			write(2, "bash: unset : not a valid identifier\n", 37);
			return (2);
		}
	}
	return (512);
}

int	ft_unset(t_mini *data, g_built *built, int loop)
{
	t_node	node;
	int		rl_std_out;

	built->end_state = 0;
	(void) built;
	if (data[0].n_of_p < 3)
		ft_here_doc(data);
	if (data[loop].std_out != NULL)
		ft_open_std_out_files_for_built(data, &node, loop);
	rl_std_out = dup(1);
	if (data[loop].std_out != NULL)
		dup2(node.file2, 1);
	if (data[loop].builtins != NULL && data[loop].opt_args != NULL)
		built->end_state = ft_unset_v1(data, built, loop);
	dup2(rl_std_out, 1);
	return (built->end_state);
}

void	ft_env(t_mini *data, g_built *built, int loop)
{
	t_node	node;
	int		rl_std_out;

	if (data[0].n_of_p < 3)
		ft_here_doc(data);
	if (data[loop].std_out != NULL)
		ft_open_std_out_files_for_built(data, &node, loop);
	rl_std_out = dup(1);
	if (data[loop].std_out != NULL)
		dup2(node.file2, 1);
	if (data[loop].builtins != NULL && data[loop].opt_args == NULL)
	{
		ft_envdup(data, built, loop);
		ft_change_shlvl(data, built);
		ft_print_env(data, built, loop);
	}
	dup2(rl_std_out, 1);
}

int	ft_export_v1(t_mini *data, g_built *built, int loop)
{
	int	a;

	a = -1;
	if (built->export == NULL)
		ft_exportdup(data, built, loop);
	ft_sort_export(data, built);
	while (++a < ft_calc_args(data, loop))
	{
		if (ft_check_var(data, a, loop))
			ft_check_export(data, built, a, loop);
		else
		{
			write(2, "bash: export : not a valid identifier\n", 38);
			return (512);
		}
	}
	return (0);
}

int	ft_export(t_mini *data, g_built *built, int loop)
{
	int		rl_std_out;
	t_node	node;

	built->end_state = 0;
	if (data[0].n_of_p < 3)
		ft_here_doc(data);
	if (data[loop].std_out != NULL)
		ft_open_std_out_files_for_built(data, &node, loop);
	rl_std_out = dup(1);
	if (data[loop].std_out != NULL)
		dup2(node.file2, 1);
	if (data[loop].builtins != NULL && data[loop].opt_args == NULL)
	{
		if (built->export == NULL)
			ft_exportdup(data, built, loop);
		ft_sort_export(data, built);
		ft_print_export(data, built, loop);
	}
	else if (data[loop].builtins != NULL && data[loop].opt_args != NULL)
		built->end_state = ft_export_v1(data, built, loop);
	dup2(rl_std_out, 1);
	return (built->end_state);
}
