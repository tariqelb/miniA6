/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_1_utilis_II.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 20:08:59 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/22 20:09:01 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"
#include "exe_header.h"

void	ft_execve_cmd_hr(t_mini *data, g_built *built, t_node *node)
{
	(void) built;
	ft_no_cmd_no_output(data, node);
	dup2(node->fd[0], 0);
	close(node->fd[0]);
	close(node->fd[1]);
	if (execve(data[0].cmd_path, data[0].opt_args, built->envp) == -1)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
}

void	ft_execve_cmd_hr_rr(t_mini *data, g_built *built, t_node *node)
{
	(void) built;
	ft_open_std_out_files(data, node, 0);
	ft_no_cmd_no_output(data, node);
	dup2(node->fd[0], 0);
	dup2(node->file2, 1);
	close(node->fd[0]);
	close(node->fd[1]);
	close(node->file2);
	if (execve(data[0].cmd_path, data[0].opt_args, built->envp) == -1)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
}
