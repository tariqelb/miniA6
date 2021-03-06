/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_of_cmd_I.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:59:42 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/22 21:59:44 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"
#include "exe_header.h"

void	ft_type_of_cmd_1_v2(t_mini *data, g_built *built, t_node *node)
{
	if (data->std_in == NULL && data->std_out == NULL)
		ft_execve_cmd(data, built, node);
	else if (data->std_in != NULL && data->std_out == NULL)
		ft_execve_cmd_lr(data, built, node);
	else if (data->std_in != NULL && data->std_out != NULL)
		ft_execve_cmd_rr_lr(data, built, node);
	else if (data->std_in == NULL && data->std_out != NULL)
		ft_execve_cmd_rr(data, built, node);
}

int	ft_type_of_cmd_1(t_mini *data, g_built *built)
{
	t_node	node;

	(void) built;
	node.pids_ads = NULL;
	if (ft_do_some_malloc_v2(&node, 1))
		return (1);
	node.num_of_cmd = data->n_of_p;
	node.loop = 0;
	if (data->limiter != NULL)
		ft_heredoc_type_of_cmd_1(&node, data, built);
	else
	{
		node.pids_ads[0] = fork();
		if (node.pids_ads[0] == -1)
			return (1);
		if (node.pids_ads[0] == 0)
			ft_type_of_cmd_1_v2(data, built, &node);
		wait_pross(&node, built);
	}
	ft_do_some_malloc_v2(&node, 0);
	return (0);
}
