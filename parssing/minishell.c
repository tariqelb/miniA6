/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 19:39:01 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/05/03 14:19:44 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../execution/exe_header.h"
#include "../builtin/builtin.h"
#include "minishell.h"

void	ft_check_if_builtin(t_mini *line, g_built *built, int loop)
{
	(void) line;
	(void) built;
	(void) loop;
	if (!ft_strncmp_magiscule(line[loop].builtins, "cd"))
		built->end_state = ft_cd(line, built);
	else if (!ft_strncmp_magiscule(line[loop].builtins, "echo"))
		built->end_state = ft_echo(line, built);
	else if (!ft_strncmp_exe(line[loop].builtins, "exit"))
		built->end_state = ft_exit(line, built);
	else if (!ft_strncmp_magiscule(line[loop].builtins, "pwd"))
		built->end_state = ft_pwd(line, built);
	else if (!ft_strncmp_exe(line[loop].builtins, "export"))
		built->end_state = ft_export(line, built, loop);
	else if (!ft_strncmp_exe(line[loop].builtins, "unset"))
		built->end_state = ft_unset(line, built, loop);
	else if (!ft_strncmp_magiscule(line[loop].builtins, "env"))
		ft_env(line, built, loop);
	if (line[0].n_of_p == 1)
		return ;
}

void	ft_minishell(t_mini *line, char **env, g_built *built)
{
	int	i;

	i = 0;
	(void) env;
	(void) built;
	(void) line;
	if (line[0].n_of_p == 1 && line[0].builtins != NULL)
		ft_check_if_builtin(line, built, 0);
	else if (ft_check_nbr_of_cmd(line, built, line->n_of_p))
			built->end_state = 1;
	/*if (line == NULL)
	 	return ;
	 while (line[i].fcl != NULL)
	 {
	  	ft_display(&line[i]);
	  	i++;
	 }*/
}

int	main(int ac, char **av, char **env)
{
	t_mini	*line;
	char	*cmd;

	line = NULL;
	ft_init_sig(&built, ac, av);
	while (1)
	{
		cmd = readline("Prompt $ ");
		built.flag = 1;
		if (ft_valide(cmd) == 1)
		{
			line = ft_init_line(line, cmd, env);
			if (ft_initialize(line, cmd, &built) == 0)
			{
				ft_minishell(line, env, &built);
				ft_free_cmd(line);
			}
			else
				built.end_state = 1;
		}
		else if (ft_valide(cmd) == -1)
			ft_sigquit_handler(1);
		ft_next_cmd(&cmd);
	}
	return (0);
}