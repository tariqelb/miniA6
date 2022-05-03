/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_type_of_cmd_II.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:42:45 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/22 21:42:46 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_header.h"
#include "../parssing/minishell.h"
#include "./get_next_line/get_next_line.h"

void	ft_drr_2(t_node *node, g_built *built, t_mini *data)
{
	(void) built;
	node->loop = 0;
	node->n_std_in_hr = -2;
	if (data[node->loop].limiter != NULL)
		node->n_std_in_hr += 2;
	node->pids_ads[0] = fork();
	if (node->pids_ads[0] == -1)
		return ;
	else if (node->pids_ads[0] == 0)
		ft_drr_2_v2(node, built, data);
	node->loop = 1;
	if (data[node->loop].limiter != NULL)
		node->n_std_in_hr += 2;
	node->pids_ads[1] = fork();
	if (node->pids_ads[1] == -1)
		return ;
	else if (node->pids_ads[1] == 0)
		ft_drr_2_v3(node, built, data);
	close_h_fd(node);
	close_fd(node);
	wait_pross(node, built);
	return ;
}

int	ft_make_some_pipe_2(t_node *node)
{
	if (pipe(&node->h_fd[0]) == -1)
		return (1);
	if (pipe(&node->h_fd[2]) == -1)
		return (1);
	return (0);
}

int	ft_heredoc_type_of_cmd_2(t_node *node, t_mini *data, g_built *built, int nbr_of_cmd)
{
	int pid;

	(void) built;
	pid = fork();
	if(pid == 0)
	{
		if (ft_make_some_pipe_2(node))
			return (1);
		if (pipe(node->fd) == -1)
			return (1);
		node->n_std_out_hr = -1;
		node->loop = -1;
		while (++node->loop < nbr_of_cmd)
		{
			if (data[node->loop].limiter != NULL)
				ft_heredoc_2(node, data, built);
		}
		ft_drr_2(node, built, data);
			exit(0);
	}
	else
		waitpid(pid, &built->end_state, 0);
	return (0);
}
