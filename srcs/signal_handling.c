/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 16:49:41 by blevrel           #+#    #+#             */
/*   Updated: 2022/10/29 14:48:16 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	signal_handler(void)
{
	signal(SIGINT, catch_signal);
	signal(SIGQUIT, SIG_IGN);
}

void	catch_signal(int signal)
{
	if (signal == SIGINT)
	{
		if (g_signal_trigger == IN_HERE_DOC)
		{
			ft_printf("\33[2K\r");
			exit(25);
		}
		else if (g_signal_trigger == IN_PARENT)
		{
			rl_on_new_line();
			ft_printf("\n");
			rl_replace_line("", 0);
			rl_redisplay();
			return ;
		}
		else if (g_signal_trigger == IN_COMMAND)
		{
			ft_printf("\n");
			return ;
		}
	}
}
