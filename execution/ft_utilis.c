/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utilis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabdelou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 21:26:02 by mabdelou          #+#    #+#             */
/*   Updated: 2022/04/22 21:26:04 by mabdelou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exe_header.h"
#include "../parssing/minishell.h"

int	ft_check_nbr_of_cmd(t_mini *data, g_built *built, int nbr_of_cmd)
{
	(void) built;
	if (nbr_of_cmd == 0)
		return (1);
	if (nbr_of_cmd == 1)
		return (ft_type_of_cmd_1(data, built));
	else if (nbr_of_cmd == 2)
		return (ft_type_of_cmd_2(data, built, nbr_of_cmd));
	else
		return (ft_type_of_cmd_3(data, built, nbr_of_cmd));
	return (0);
}
