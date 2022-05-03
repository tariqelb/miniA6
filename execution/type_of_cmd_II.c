/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_cmd_II.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 22:01:13 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/22 22:01:14 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"
#include "exe_header.h"

void	ft_type_of_cmd_2_v3(t_mini *data, g_built *built, t_node *node)
{
	(void) built;
	if (node->loop == 0 && data[node->loop].std_in != NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_1_lr(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_1(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in != NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_1_lr_rr(data, built, node);
	else if (node->loop == 0 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_1_rr(data, built, node);
	else if (node->loop == 1 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_2_rr(data, built, node);
	else if (node->loop == 1 && data[node->loop].std_in != NULL
		&& data[node->loop].std_out != NULL)
		ft_execve_cmd_2_lr_rr(data, built, node);
	else if (node->loop == 1 && data[node->loop].std_in != NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_2_lr(data, built, node);
	else if (node->loop == 1 && data[node->loop].std_in == NULL
		&& data[node->loop].std_out == NULL)
		ft_execve_cmd_2(data, built, node);
}

int	ft_type_of_cmd_2_v2(t_mini *data, g_built *built, t_node *node)
{
	node->pids_ads[node->loop] = fork();
	if (node->pids_ads[node->loop] == 0 && data[node->loop].builtins != NULL)
		ft_execve_builtin(data, built, node);
	if (node->pids_ads[node->loop] == -1)
		return (1);
	else if (node->pids_ads[node->loop] == 0)
		ft_type_of_cmd_2_v3(data, built, node);
	return (0);
}

int	ft_type_of_cmd_2(t_mini *data, g_built *built, int nbr_of_cmd)
{
	t_node	node;

	(void) built;
	node.pids_ads = NULL;
	node.num_of_cmd = data->n_of_p;
	if (ft_do_some_malloc_v2(&node, 1))
		return (1);
	if (data->limiter != NULL || data[1].limiter != NULL)
		ft_heredoc_type_of_cmd_2(&node, data, built, nbr_of_cmd);
	else
	{
		if (pipe(node.fd) == -1)
			return (1);
		node.loop = -1;
		while (++node.loop < nbr_of_cmd)
		{
			if (ft_type_of_cmd_2_v2(data, built, &node))
				return (1);
		}
		close_fd(&node);
		wait_pross(&node, built);
	}
	ft_do_some_malloc_v2(&node, 0);
	return (0);
}
