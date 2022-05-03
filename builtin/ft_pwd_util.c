/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 22:25:09 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/05/03 14:07:33 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parssing/minishell.h"
#include "builtin.h"

int	ft_print_pwd(int *fds, char *pwd, int i)
{
	int	index;
	int	len;

	len = ft_strlen(pwd);
	index = 0;
	while (index < i)
	{
		write(fds[index], pwd, len);
		write(fds[index], "\n", 1);
		index++;
	}
	free(pwd);
	free(fds);
	return (0);
}
