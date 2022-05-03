/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_cmd_III.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:04:23 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/22 22:04:24 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"
#include "exe_header.h"

void	ft_type_of_cmd_3_v5(t_mini *data, t_node *node,
		g_built *built, int nbr_of_cmd)
{
	(void) built;
	if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in == NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_4_rr(data, built, node);
	else if (node->loop == (nbr_of_cmd - 1)
		&& data[node->loop].std_in == NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_5(data, built, node);
	else if (node->loop == (nbr_of_cmd - 1)
		&& data[node->loop].std_in != NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_5_lr_rr(data, built, node);
	else if (node->loop == (nbr_of_cmd - 1)
		&& data[node->loop].std_in == NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_5_rr(data, built, node);
	else if (node->loop == (nbr_of_cmd - 1)
		&& data[node->loop].std_in != NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_5_lr(data, built, node);
}

void	ft_type_of_cmd_3_v4(t_mini *data, t_node *node,
		g_built *built, int nbr_of_cmd)
{
	(void) built;
	if (node->loop == 0 && data[node->loop].std_in != NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_3_lr(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_3(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in != NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_3_lr_rr(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_3_rr(data, built, node);
	else if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in != NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_4_lr(data, built, node);
	else if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in == NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_4(data, built, node);
	else if (node->loop > 0 && node->loop < (nbr_of_cmd - 1)
		&& data[node->loop].std_in != NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_4_lr_rr(data, built, node);
}

int	ft_type_of_cmd_3_v3(t_mini *data,
		t_node *node, g_built *built, int nbr_of_cmd)
{
	++node->n_std_in_c;
	node->n_std_out_c += 2;
	node->pids_ads[node->loop] = fork();
	if (node->pids_ads[node->loop] == -1)
		return (1);
	else if (node->pids_ads[node->loop] == 0)
	{
		if (node->pids_ads[node->loop] == 0
			&& data[node->loop].builtins != NULL)
			ft_execve_builtin(data, built, node);
		ft_type_of_cmd_3_v4(data, node, built, nbr_of_cmd);
		ft_type_of_cmd_3_v5(data, node, built, nbr_of_cmd);
	}
	return (0);
}

int	ft_type_of_cmd_3_v2(t_mini *data,
		t_node *node, g_built *built, int nbr_of_cmd)
{
	(void) built;
	node->pids_ads = NULL;
	if (ft_do_some_malloc_v2(node, 1) || ft_do_some_malloc(node, 0))
		return (1);
	make_pipes(node);
	node->loop = -1;
	node->n_std_in_c = -3;
	node->n_std_out_c = -1;
	while (++node->loop < nbr_of_cmd)
	{
		if (ft_type_of_cmd_3_v3(data, node, built, nbr_of_cmd))
			return (1);
	}
	close_fds(node);
	wait_pross(node, built);
	ft_free_some_ptrs(node, 0);
	ft_do_some_malloc_v2(node, 0);
	return (0);
}

int	ft_type_of_cmd_3(t_mini *data, g_built *built, int nbr_of_cmd)
{
	t_node	node;

	(void) built;
	node.num_of_cmd = data->n_of_p;
	node.loop = 0;
	if (data[node.loop].limiter != NULL)
		ft_heredoc_type_of_cmd_3(&node, data, built, nbr_of_cmd);
	else
		return (ft_type_of_cmd_3_v2(data, &node, built, nbr_of_cmd));
	return (0);
}
