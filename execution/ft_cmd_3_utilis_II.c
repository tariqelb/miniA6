/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_3_utilis_II.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:09:58 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/22 21:10:06 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"
#include "exe_header.h"

void	ft_execve_cmd_4_rr(t_mini *data, g_built *built, t_node *node)
{
	(void) built;
	ft_open_std_out_files(data, node, node->loop);
	ft_no_cmd_no_output(data, node);
	dup2(node->fds[node->loop + node->n_std_in_c], 0);
	dup2(node->file2, 1);
	close_fds(node);
	close(node->file2);
	if (execve(data[node->loop].cmd_path,
			data[node->loop].opt_args, built->envp) == -1)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
}

void	ft_execve_cmd_4_lr_rr(t_mini *data, g_built *built, t_node *node)
{
	(void) built;
	ft_open_std_in_files(data, node, node->loop);
	ft_open_std_out_files(data, node, node->loop);
	ft_no_cmd_no_output(data, node);
	dup2(node->file1, 0);
	dup2(node->file2, 1);
	close(node->file2);
	close_fds(node);
	close(node->file1);
	if (execve(data[node->loop].cmd_path,
			data[node->loop].opt_args, built->envp) == -1)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
}

void	ft_execve_cmd_4_lr(t_mini *data, g_built *built, t_node *node)
{
	(void) built;
	ft_open_std_in_files(data, node, node->loop);
	ft_no_cmd_no_output(data, node);
	dup2(node->file1, 0);
	dup2(node->fds[node->n_std_out_c], 1);
	close_fds(node);
	close(node->file1);
	if (execve(data[node->loop].cmd_path,
			data[node->loop].opt_args, built->envp) == -1)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
}

void	ft_execve_cmd_5(t_mini *data, g_built *built, t_node *node)
{
	(void) built;
	ft_no_cmd_no_output(data, node);
	dup2(node->fds[node->loop + node->n_std_in_c], 0);
	close_fds(node);
	if (execve(data[node->loop].cmd_path,
			data[node->loop].opt_args, built->envp) == -1)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
}

void	ft_execve_cmd_5_rr(t_mini *data, g_built *built, t_node *node)
{
	(void) built;
	ft_open_std_out_files(data, node, node->loop);
	ft_no_cmd_no_output(data, node);
	dup2(node->fds[node->loop + node->n_std_in_c], 0);
	dup2(node->file2, 1);
	close(node->file2);
	close_fds(node);
	if (execve(data[node->loop].cmd_path,
			data[node->loop].opt_args, built->envp) == -1)
	{
		write(2, "command not found\n", 18);
		exit(127);
	}
}
