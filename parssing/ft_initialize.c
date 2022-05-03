/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 21:07:57 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/05/03 13:26:01 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../builtin/builtin.h"

int	ft_initialize_util(t_mini *line, char **cmds, char **env)
{
	int	i;

	i = 0;
	while (cmds[i])
	{
		line[i].fcl = line[0].fcl;
		line[i].f_cmd = cmds[i];
		if (ft_parse(&line, i, cmds[i], env) == 1)
			return (1);
		i++;
	}
	free(cmds[i]);
	free(cmds);
	line[i].fcl = NULL;
	ft_handle_order(line);
	return (0);
}

t_mini	*ft_prevent_from_sig(t_mini *line, char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i] != NULL)
		i++;
	line[i].fcl = NULL;
	return (line);
}

int	ft_initialize(t_mini *line, char *cmd, g_built *built)
{
	char	**cmds;

	if (cmd == NULL)
		return (1);
	add_history(cmd);
	if (ft_handle_quotes(line, cmd, built))
		return (1);
	cmds = ft_split_case(line->fcl, '|');
	line = ft_prevent_from_sig(line, cmds);
	line[0].fcl = ft_add_space_besides(line[0].fcl);
	if (ft_check_cmd_err(line, cmd))
	{
		if (cmds)
			ft_free_tab(cmds, NULL, NULL);
		return (1);
	}
	if (cmds == NULL)
		return (1);
	if (built->envp == NULL)
		ft_envdup(line, built, 0);
	if (ft_initialize_util(line, cmds, built->envp) == 1)
		return (ft_free_a(cmds));
	return (0);
}

int	ft_number_of_pipe(char *cmd)
{
	char	**str;
	int		i;

	str = NULL;
	i = 0;
	str = ft_split_case(cmd, '|');
	if (str == NULL)
		return (0);
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (i);
}

void	ft_init(t_mini **line, int nbr, char **env)
{
	int	i;

	i = 0;
	while (i < nbr)
	{
		line[0][i].fcl = NULL;
		line[0][i].f_cmd = NULL;
		line[0][i].cmd_path = NULL;
		line[0][i].opt_args = NULL;
		line[0][i].builtins = NULL;
		line[0][i].cmd = NULL;
		line[0][i].std_in = NULL;
		line[0][i].std_out = NULL;
		line[0][i].limiter = NULL;
		line[0][i].trunc = NULL;
		line[0][i].env = env;
		line[0][i].order = NULL;
		line[0][i].orlim = NULL;
		line[0][i].f_ord = NULL;
		line[0][i].f_o_d = NULL;
		line[0][i].error = NULL;
		line[0][i].n_of_p = nbr;
		line[0][i].redi = 0;
		i++;
	}
}
