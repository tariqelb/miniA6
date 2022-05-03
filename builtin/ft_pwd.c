/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 16:16:19 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/05/03 14:07:15 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"
#include "builtin.h"

int	ft_pwd_util_two(char **tmp)
{
	if (ft_strcmp(tmp[0], "-") == 0)
		return (0);
	if (ft_strcmp(tmp[0], "--") == 0)
		return (0);
	if (ft_strcmp(tmp[0], "---") == 0)
	{
		write(2, "pwd: bad option: ", 17);
		write(2, tmp[0] + 1, ft_strlen(tmp[0] + 1));
		write(2, "\n", 1);
		return (1);
	}
	write(2, "pwd: too many arguments\n", 24);
	return (1);
}

int	ft_pwd_util(t_mini *line)
{
	int		len;
	char	**tmp;

	tmp = line[0].opt_args;
	len = 0;
	while (tmp && tmp[len])
		len++;
	if (len == 0)
		return (0);
	if (len == 1)
		return (ft_pwd_util_two(tmp));
	else if (len > 1)
	{
		if (line[0].std_in == NULL && line[0].std_out == NULL)
		{
			write(2, "pwd: too many arguments\n", 24);
			return (1);
		}
	}
	return (0);
}

int	ft_check_pwd_error(t_mini *line)
{
	if (line[0].opt_args != NULL)
	{
		if (line[0].std_in != NULL)
			if (ft_strcmp(line[0].opt_args[0], line[0].std_in[0]) != 0)
				return (0);
		if (line[0].std_out != NULL)
			if (ft_strcmp(line[0].opt_args[0], line[0].std_out[0]) != 0)
				return (0);
		return (1);
	}
	return (0);
}

int	ft_pwd_util_three(t_mini *line, char *pwd, int i)
{
	int	*fds;

	if (ft_check_pwd_error(line))
	{
		free(pwd);
		write(2, "pwd: too many arguments\n", 24);
		return (1);
	}
	i = 0;
	while (line[0].std_out && line[0].std_out[i])
		i++;
	if (i)
	{
		fds = (int *) malloc(sizeof(int) * i);
		fds = ft_open_files(line, fds, i);
		return (ft_print_pwd(fds, pwd, i));
	}
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

int	ft_pwd(t_mini *line, g_built *built)
{
	char	*pwd;
	int		stt;

	stt = ft_here_doc(line);
	if (line[0].error != NULL)
	{
		write(2, line[0].error, ft_strlen(line[0].error));
		return (write(2, "\n", 1));
	}
	if (ft_file_in(line) || ft_file_out(line))
		return (1);
	if (ft_pwd_util(line))
		return (1);
	pwd = NULL;
	pwd = (char *) malloc(sizeof(char) * 4096);
	if (built && built->envp == NULL)
		ft_envdup(line, built, 0);
	pwd = ft_get_env_var(built->envp, "PWD", pwd);
	if (pwd == NULL)
	{
		free(pwd);
		return (1);
	}
	return (ft_pwd_util_three(line, pwd, stt));
}
