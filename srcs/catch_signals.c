/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blevrel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 11:09:01 by blevrel           #+#    #+#             */
/*   Updated: 2022/11/21 10:39:14 by blevrel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	catch_signal(int signal)
{
	if (signal == SIGINT)
	{
		rl_on_new_line();
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal_trigger = -2;
	}
}

void	catch_signal_here_doc(int signal)
{
	if (signal == SIGINT)
	{
		ft_printf("\n");
		close(0);
		g_signal_trigger = -1;
	}
}
