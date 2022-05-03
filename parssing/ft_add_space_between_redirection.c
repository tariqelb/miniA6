/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space_between_redirection.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 01:23:11 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/04/30 21:03:39 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_handle_quotes_util(char *cmds, int k, char c)
{
	int	j;

	j = 1;
	while (cmds[j])
	{
		if (cmds[j] == c && cmds[j + 1] == 0)
		{
			k++;
			j++;
		}
		else
		{
			if (cmds[j] == c && cmds[j + 1])
				k++;
			else
				cmds[j - 1 - k] = cmds[j];
			j++;
		}
	}
	cmds[j - 1 - k] = 0;
	return (cmds);
}

char	**ft_remove_quotes(char **cmds)
{
	int		i;
	char	c;
	int		k;

	i = 0;
	k = 0;
	while (cmds[i])
	{
		if (cmds[i][0] == 34 || cmds[i][0] == 39)
		{
			c = 39;
			if (cmds[i][0] == 34)
				c = 34;
			cmds[i] = ft_handle_quotes_util(cmds[i], k, c);
		}
		i++;
	}
	return (cmds);
}
char	*ft_adjust(char *t, int add)
{
	char	*rslt;
	int		i;
	int		j;

	rslt = (char *) malloc(sizeof(char) * (add + ft_strlen(t) + 1));
	j = 0;
	i = 0;
	while (t[i])
	{
		if (t[i] == '<' || t[i] == '>' || t[i] == '|')
		{
			rslt[j++] = ' ';
			while (t[i] && (t[i] == '<' || t[i] == '>' || t[i] == '|'))
				rslt[j++] = t[i++];
			rslt[j++] = ' ';
		}
		rslt[j++] = t[i++];
	}
	rslt[j] = 0;
	return (rslt);
}

int	ft_count_space(char *str)
{
	int	i;
	int	add;

	add = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '<' || str[i] == '>' || str[i] == '|')
		{
			add++;
			while (str[i] && (str[i] == '<' || str[i] == '>' || str[i] == '|'))
				i++;
			add++;
		}
		i++;
	}
	return (add);
}

char	*ft_add_space_besides(char *token)
{
	int		add;
	char	*tmp;

	if (token == NULL)
		return (NULL);
	add = 0;
	add = ft_count_space(token);
	if (add > 1)
	{
		tmp = ft_adjust(token, add);
		free(token);
		token = tmp;
	}
	return (token);
}
