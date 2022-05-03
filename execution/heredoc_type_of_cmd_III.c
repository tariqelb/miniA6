/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_type_of_cmd_III.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:46:22 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/22 21:46:24 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_header.h"
#include "../parssing/minishell.h"
#include "./get_next_line/get_next_line.h"

void	ft_drr_3_v4(t_node *node, t_mini *data, g_built *built, int nbr_of_cmd)
{
	(void) built;
	if (node->loop == (nbr_of_cmd - 1) && data[node->loop].std_in == NULL
		&& data[node->loop].std_out == NULL
		&& data[node->loop].limiter != NULL)
		ft_execve_cmd_5_hr(data, built, node);
	else if (node->loop == (nbr_of_cmd - 1) && data[node->loop].std_in == NULL
		&& data[node->loop].std_out != NULL
		&& data[node->loop].limiter != NULL)
		ft_execve_cmd_5_hr_rr(data, built, node);
	else if (node->loop == (nbr_of_cmd - 1) && data[node->loop].std_in == NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_5__(data, built, node);
	else if (node->loop == (nbr_of_cmd - 1) && data[node->loop].std_in != NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_5_lr_rr__(data, built, node);
	else if (node->loop == (nbr_of_cmd - 1) && data[node->loop].std_in == NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_5_rr__(data, built, node);
	else if (node->loop == (nbr_of_cmd - 1) && data[node->loop].std_in != NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_5_lr__(data, built, node);
}

void	ft_drr_3_v3(t_node *node, t_mini *data, g_built *built, int nbr_of_cmd)
{
	(void) built;
	if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in == NULL && data[node->loop].std_out == NULL
		&& data[node->loop].limiter != NULL)
		ft_execve_cmd_4_hr(data, built, node);
	else if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in == NULL && data[node->loop].std_out != NULL
		&& data[node->loop].limiter != NULL)
		ft_execve_cmd_4_hr_rr(data, built, node);
	else if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in != NULL && data[node->loop].std_out == NULL)
		ft_execve_cmd_4_lr__(data, built, node);
	else if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in == NULL && data[node->loop].std_out == NULL)
		ft_execve_cmd_4__(data, built, node);
	else if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in != NULL && data[node->loop].std_out != NULL)
		ft_execve_cmd_4_lr_rr__(data, built, node);
	else if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in == NULL && data[node->loop].std_out != NULL)
		ft_execve_cmd_4_rr__(data, built, node);
	ft_drr_3_v4(node, data, built, nbr_of_cmd);
}

void	ft_drr_3_v2(t_node *node, t_mini *data, g_built *built, int nbr_of_cmd)
{
	(void) built;
	if (node->pids_ads[node->loop] == 0 && data[node->loop].builtins != NULL)
		ft_execve_builtin(data, built, node);
	if (node->loop == 0 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out == NULL && data[node->loop].limiter != NULL)
		ft_execve_cmd_3_hr(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out != NULL && data[node->loop].limiter != NULL)
		ft_execve_cmd_3_hr_rr(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in != NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_3_lr__(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_3__(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in != NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_3_lr_rr__(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_3_rr__(data, built, node);
	ft_drr_3_v3(node, data, built, nbr_of_cmd);
}

int	ft_drr_3(t_node *node, t_mini *data, g_built *built, int nbr_of_cmd)
{
	(void) built;
	node->loop = -1;
	node->n_std_in_c = -4;
	node->n_std_out_c = -1;
	node->n_std_in_hr = -2;
	while (++node->loop < nbr_of_cmd)
	{
		node->n_std_in_c += 2;
		node->n_std_out_c += 2;
		if (data[node->loop].limiter != NULL)
			node->n_std_in_hr += 2;
		node->pids_ads[node->loop] = fork();
		if (node->pids_ads[node->loop] == -1)
			return (1);
		else if (node->pids_ads[node->loop] == 0)
			ft_drr_3_v2(node, data, built, nbr_of_cmd);
	}
	close_fds(node);
	close_h_fds(node);
	wait_pross(node, built);
	return (0);
}

int	ft_heredoc_type_of_cmd_3(t_node *node, t_mini *data,
	g_built *built, int nbr_of_cmd)
{
	int pid;

	(void) built;
	pid = fork();
	if (pid == 0)
	{
		node->num_of_hr = ft_calc_num_of_heredoc(data);
		if (ft_do_some_malloc(node, 0)
			|| ft_do_some_malloc(node, node->num_of_hr))
			exit(1);
		node->loop = -1;
		node->n_std_out_hr = -1;
		while (++node->loop < nbr_of_cmd)
		{
			if (data[node->loop].limiter != NULL)
				ft_heredoc_3(node, data, built);
		}
		if (ft_drr_3(node, data, built, nbr_of_cmd))
			write(2, "ERROR can't make prosess\n", 25);
		ft_free_some_ptrs(node, 0);
		ft_free_some_ptrs(node, node->num_of_hr);
		exit(0);
	}
	else
		waitpid(pid, &built->end_state, 0);
	return (0);
}
