/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:00:38 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/05/03 14:19:55 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(char *cmd, int i)
{
	int		j;
	int		len;
	char	*env;

	len = 0;
	j = i;
	while (cmd[i] && ((cmd[i] >= 'A' && cmd[i] <= 'Z')
			|| (cmd[i] >= 'a' && cmd[i] <= 'z')
			|| (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == 63))
	{
		len++;
		i++;
	}
	env = (char *) malloc(sizeof(char) * len + 1);
	i = 0;
	while (i < len)
	{
		env[i] = cmd[j];
		i++;
		j++;
	}
	env[i] = 0;
	return (env);
}

char	*ft_get_env_val(char *env_n, char **env)
{
	int		i;
	int		len;
	char	*env_cp;

	len = ft_strlen(env_n);
	i = -1;
	if (ft_strncmp(env_n, "path", 4) == 0)
	{
		while (++i < 4)
			env_n[i] = env_n[i] - 32;
	}
	i = 0;
	while (env[i])
	{
		env_cp = ft_env_copy(env_cp, env[i]);
		if (ft_strcmp(env_n, env_cp) == 0)
			return (&env[i][len + 1]);
		if (env_cp != NULL)
			free(env_cp);
		i++;
	}
	return (NULL);
}

char	*ft_get_expand(char *env_name, char **env)
{
	char	*env_val;

	env_val = NULL;
	env_val = ft_get_env_val(env_name, env);
	if (env_val == NULL)
		return (NULL);
	return (env_val);
}

int	ft_expand_util(t_mini *line, char **fcl, char *cmd, g_built *built)
{
	char	*exp;
	char	*v_exp;

	(void) line;
	if (built->envp == NULL)
		built = ft_initialize_env(line, built);
	v_exp = ft_get_env(cmd, built->i + 1);
	if (ft_strncmp(v_exp, "?", 1) == 0)
		exp = ft_itoa(WEXITSTATUS(built->end_state));
	else
		exp = ft_get_expand(v_exp, built->envp);
	if (exp != NULL)
		fcl[0] = ft_strjoin_free(fcl[0], exp);
	built->i = built->i + ft_strlen(v_exp);
	free(v_exp);
	return (built->i);
}

char	*ft_expand(t_mini *line, char **fcl, char *cmd, g_built *built)
{
	char	*c;
	int		*flag;

	built->i = -1;
	fcl[0] = (char *) malloc(1);
	ft_expand_init(&c, &flag, fcl);
	while (cmd[++built->i])
	{
		c[0] = cmd[built->i];
		if (cmd[built->i] == 34 && flag[1] == 0)
			flag[0]++;
		if (cmd[built->i] == 39 && flag[0] == 0)
			flag[1]++;
		if (flag[0] == 2)
			flag[0] = 0;
		if (flag[1] == 2)
			flag[1] = 0;
		if (cmd[built->i] == '$' && (flag[0] || (flag[0] == 0 && flag[1] == 0)))
			built->i = ft_expand_util(line, &fcl[0], cmd, built);
		else
			fcl[0] = ft_strjoin_free(fcl[0], c);
	}
	free(c);
	free(flag);
	return (fcl[0]);
}
