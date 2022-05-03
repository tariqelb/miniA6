/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_display.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tel-bouh <tel-bouh@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 21:23:54 by tel-bouh          #+#    #+#             */
/*   Updated: 2022/04/21 15:59:22 by tel-bouh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_display(t_mini *line)
{
	int	i;

	if (line->fcl != NULL)
	{
		i = 0;
		printf("fcl      : %s\n", line->fcl);
		printf("f_cmd    : %s\n", line->f_cmd);
		printf("cmd      : %s\n", line->cmd);
		printf("cmd_path : %s\n", line->cmd_path);
		printf("builtins : %s\n", line->builtins);
		printf("stdin    : ");
		while (line->std_in && line->std_in[i])
		{
			printf("%s\t", line->std_in[i]);
			i++;
		}
		printf("\n");
		i = 0;
		printf("stdout   : ");
		while (line->std_out && line->std_out[i])
		{
			printf("%s\t", line->std_out[i]);
			i++;
		}
		printf("\n");
		i = 0;
		printf("trunc    : ");
		while (line->trunc && line->trunc[i])
		{
			printf("%s\t", line->trunc[i]);
			i++;
		}
		printf("\n");
		i = 0;
		printf("limiter  : ");
		while (line->limiter && line->limiter[i])
		{
			printf("%s\t", line->limiter[i]);
			i++;
		}
		i = 0;
		printf("\n");
		printf("opt_args : ");
		while (line->opt_args && line->opt_args[i])
		{
			printf("%s\t", line->opt_args[i]);
			i++;
		}
		i = 0;
		printf("\nnbr_of_pipe :%d\n", line->n_of_p);
		i = 0;
		printf("order : ");
		while (line->order && line->order[i])
		{
			printf("%s\t", line->order[i]);
			i++;
		}
		printf("\n");
		i = 0;
		printf("orlim : ");
		while (line->orlim && line->orlim[i])
		{
			printf("%s\t", line->orlim[i]);
			i++;
		}
		printf("\n");
		i = 0;
		printf("f_ord : ");
		while (line->f_ord && line->f_ord[i])
		{
			printf("%s\t", line->f_ord[i]);
			i++;
		}
		printf("\n");
		i = 0;
		printf("f_o_d : ");
		while (line->f_o_d && line->f_o_d[i])
		{
			printf("%s\t", line->f_o_d[i]);
			i++;
		}
		if (line->error)
			printf("\nError   : %s\n", line->error);
		printf("\n-------------------------------------------------------------------\n");
	}
}
