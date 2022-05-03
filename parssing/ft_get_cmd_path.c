/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_cmd_path.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 22:21:33 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/04/25 14:56:49 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_get_paths(char **env)
{
	int		i;
	char	*paths;

	paths = NULL;
	i = 0;
	while (env[i] != NULL)
	{
		if (env[i][0] == 'P' && env[i][1] == 'A' && env[i][2] == 'T'
			&& env[i][3] == 'H' && env[i][4] == '=')
		{
			paths = env[i];
			return (ft_split(paths + 5, ':'));
		}
		else
			i++;
	}
	return (NULL);
}

t_mini	ft_get_cmd_path(t_mini *line, char **env)
{
	int		i;
	char	**paths;
	char	*cmd;
	char	*cmd_path;

	cmd = ft_strjoin("/", ft_rm_quotes(line[0].cmd));
	paths = ft_get_paths(env);
	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (access(cmd_path, R_OK) == 0)
		{
			line[0].cmd_path = ft_strdup(cmd_path);
			ft_free_a(paths);
			free(cmd_path);
			free(cmd);
			return (line[0]);
		}
		free(cmd_path);
	}
	line[0].cmd_path = ft_strdup(line[0].cmd);
	ft_free_a(paths);
	free(cmd);
	return (line[0]);
}
